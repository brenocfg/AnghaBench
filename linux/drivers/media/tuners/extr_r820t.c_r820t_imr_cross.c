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
struct r820t_sect_type {int gain_x; int phase_y; int value; } ;
struct r820t_priv {int dummy; } ;

/* Variables and functions */
 int r820t_multi_read (struct r820t_priv*) ; 
 int r820t_read_cache_reg (struct r820t_priv*,int) ; 
 int r820t_write_reg (struct r820t_priv*,int,int) ; 

__attribute__((used)) static int r820t_imr_cross(struct r820t_priv *priv,
			   struct r820t_sect_type iq_point[3],
			   u8 *x_direct)
{
	struct r820t_sect_type cross[5]; /* (0,0)(0,Q-1)(0,I-1)(Q-1,0)(I-1,0) */
	struct r820t_sect_type tmp;
	int i, rc;
	u8 reg08, reg09;

	reg08 = r820t_read_cache_reg(priv, 8) & 0xc0;
	reg09 = r820t_read_cache_reg(priv, 9) & 0xc0;

	tmp.gain_x = 0;
	tmp.phase_y = 0;
	tmp.value = 255;

	for (i = 0; i < 5; i++) {
		switch (i) {
		case 0:
			cross[i].gain_x  = reg08;
			cross[i].phase_y = reg09;
			break;
		case 1:
			cross[i].gain_x  = reg08;		/* 0 */
			cross[i].phase_y = reg09 + 1;		/* Q-1 */
			break;
		case 2:
			cross[i].gain_x  = reg08;		/* 0 */
			cross[i].phase_y = (reg09 | 0x20) + 1;	/* I-1 */
			break;
		case 3:
			cross[i].gain_x  = reg08 + 1;		/* Q-1 */
			cross[i].phase_y = reg09;
			break;
		default:
			cross[i].gain_x  = (reg08 | 0x20) + 1;	/* I-1 */
			cross[i].phase_y = reg09;
		}

		rc = r820t_write_reg(priv, 0x08, cross[i].gain_x);
		if (rc < 0)
			return rc;

		rc = r820t_write_reg(priv, 0x09, cross[i].phase_y);
		if (rc < 0)
			return rc;

		rc = r820t_multi_read(priv);
		if (rc < 0)
			return rc;

		cross[i].value = rc;

		if (cross[i].value < tmp.value)
			tmp = cross[i];
	}

	if ((tmp.phase_y & 0x1f) == 1) {	/* y-direction */
		*x_direct = 0;

		iq_point[0] = cross[0];
		iq_point[1] = cross[1];
		iq_point[2] = cross[2];
	} else {				/* (0,0) or x-direction */
		*x_direct = 1;

		iq_point[0] = cross[0];
		iq_point[1] = cross[3];
		iq_point[2] = cross[4];
	}
	return 0;
}