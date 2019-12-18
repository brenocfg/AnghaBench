#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct r820t_sect_type {int phase_y; int gain_x; int value; } ;
struct r820t_priv {int dummy; } ;

/* Variables and functions */
 int IMR_TRIAL ; 
 int r820t_multi_read (struct r820t_priv*) ; 
 int r820t_write_reg (struct r820t_priv*,int,int) ; 

__attribute__((used)) static int r820t_compre_step(struct r820t_priv *priv,
			     struct r820t_sect_type iq[3], u8 reg)
{
	int rc;
	struct r820t_sect_type tmp;

	/*
	 * Purpose: if (Gain<9 or Phase<9), Gain+1 or Phase+1 and compare
	 * with min value:
	 *  new < min => update to min and continue
	 *  new > min => Exit
	 */

	/* min value already saved in iq[0] */
	tmp.phase_y = iq[0].phase_y;
	tmp.gain_x  = iq[0].gain_x;

	while (((tmp.gain_x & 0x1f) < IMR_TRIAL) &&
	      ((tmp.phase_y & 0x1f) < IMR_TRIAL)) {
		if (reg == 0x08)
			tmp.gain_x++;
		else
			tmp.phase_y++;

		rc = r820t_write_reg(priv, 0x08, tmp.gain_x);
		if (rc < 0)
			return rc;

		rc = r820t_write_reg(priv, 0x09, tmp.phase_y);
		if (rc < 0)
			return rc;

		rc = r820t_multi_read(priv);
		if (rc < 0)
			return rc;
		tmp.value = rc;

		if (tmp.value <= iq[0].value) {
			iq[0].gain_x  = tmp.gain_x;
			iq[0].phase_y = tmp.phase_y;
			iq[0].value   = tmp.value;
		} else {
			return 0;
		}

	}

	return 0;
}