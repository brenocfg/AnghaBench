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
struct r820t_sect_type {int value; int gain_x; int phase_y; } ;
struct r820t_priv {int dummy; } ;

/* Variables and functions */
 int r820t_multi_read (struct r820t_priv*) ; 
 int r820t_write_reg (struct r820t_priv*,int,int) ; 

__attribute__((used)) static int r820t_iq_tree(struct r820t_priv *priv,
			 struct r820t_sect_type iq[3],
			 u8 fix_val, u8 var_val, u8 fix_reg)
{
	int rc, i;
	u8 tmp, var_reg;

	/*
	 * record IMC results by input gain/phase location then adjust
	 * gain or phase positive 1 step and negative 1 step,
	 * both record results
	 */

	if (fix_reg == 0x08)
		var_reg = 0x09;
	else
		var_reg = 0x08;

	for (i = 0; i < 3; i++) {
		rc = r820t_write_reg(priv, fix_reg, fix_val);
		if (rc < 0)
			return rc;

		rc = r820t_write_reg(priv, var_reg, var_val);
		if (rc < 0)
			return rc;

		rc = r820t_multi_read(priv);
		if (rc < 0)
			return rc;
		iq[i].value = rc;

		if (fix_reg == 0x08) {
			iq[i].gain_x  = fix_val;
			iq[i].phase_y = var_val;
		} else {
			iq[i].phase_y = fix_val;
			iq[i].gain_x  = var_val;
		}

		if (i == 0) {  /* try right-side point */
			var_val++;
		} else if (i == 1) { /* try left-side point */
			 /* if absolute location is 1, change I/Q direction */
			if ((var_val & 0x1f) < 0x02) {
				tmp = 2 - (var_val & 0x1f);

				/* b[5]:I/Q selection. 0:Q-path, 1:I-path */
				if (var_val & 0x20) {
					var_val &= 0xc0;
					var_val |= tmp;
				} else {
					var_val |= 0x20 | tmp;
				}
			} else {
				var_val -= 2;
			}
		}
	}

	return 0;
}