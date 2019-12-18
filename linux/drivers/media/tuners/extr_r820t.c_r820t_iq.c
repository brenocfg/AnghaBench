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
struct r820t_sect_type {int /*<<< orphan*/  phase_y; int /*<<< orphan*/  gain_x; } ;
struct r820t_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  r820t_compre_cor (struct r820t_sect_type*) ; 
 int r820t_compre_step (struct r820t_priv*,struct r820t_sect_type*,int) ; 
 int r820t_imr_cross (struct r820t_priv*,struct r820t_sect_type*,int*) ; 
 int r820t_iq_tree (struct r820t_priv*,struct r820t_sect_type*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int r820t_section (struct r820t_priv*,struct r820t_sect_type*) ; 
 int /*<<< orphan*/  r820t_vga_adjust (struct r820t_priv*) ; 
 int r820t_write_reg_mask (struct r820t_priv*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int r820t_iq(struct r820t_priv *priv, struct r820t_sect_type *iq_pont)
{
	struct r820t_sect_type compare_iq[3];
	int rc;
	u8 x_direction = 0;  /* 1:x, 0:y */
	u8 dir_reg, other_reg;

	r820t_vga_adjust(priv);

	rc = r820t_imr_cross(priv, compare_iq, &x_direction);
	if (rc < 0)
		return rc;

	if (x_direction == 1) {
		dir_reg   = 0x08;
		other_reg = 0x09;
	} else {
		dir_reg   = 0x09;
		other_reg = 0x08;
	}

	/* compare and find min of 3 points. determine i/q direction */
	r820t_compre_cor(compare_iq);

	/* increase step to find min value of this direction */
	rc = r820t_compre_step(priv, compare_iq, dir_reg);
	if (rc < 0)
		return rc;

	/* the other direction */
	rc = r820t_iq_tree(priv, compare_iq,  compare_iq[0].gain_x,
				compare_iq[0].phase_y, dir_reg);
	if (rc < 0)
		return rc;

	/* compare and find min of 3 points. determine i/q direction */
	r820t_compre_cor(compare_iq);

	/* increase step to find min value on this direction */
	rc = r820t_compre_step(priv, compare_iq, other_reg);
	if (rc < 0)
		return rc;

	/* check 3 points again */
	rc = r820t_iq_tree(priv, compare_iq,  compare_iq[0].gain_x,
				compare_iq[0].phase_y, other_reg);
	if (rc < 0)
		return rc;

	r820t_compre_cor(compare_iq);

	/* section-9 check */
	rc = r820t_section(priv, compare_iq);

	*iq_pont = compare_iq[0];

	/* reset gain/phase control setting */
	rc = r820t_write_reg_mask(priv, 0x08, 0, 0x3f);
	if (rc < 0)
		return rc;

	rc = r820t_write_reg_mask(priv, 0x09, 0, 0x3f);

	return rc;
}