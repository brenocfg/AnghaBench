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
typedef  scalar_t__ u8 ;
struct dcon_priv {scalar_t__ bl_val; int disp_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCON_REG_BRIGHT ; 
 int /*<<< orphan*/  DCON_REG_MODE ; 
 int MODE_BL_ENABLE ; 
 int /*<<< orphan*/  dcon_write (struct dcon_priv*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void dcon_set_backlight(struct dcon_priv *dcon, u8 level)
{
	dcon->bl_val = level;
	dcon_write(dcon, DCON_REG_BRIGHT, dcon->bl_val);

	/* Purposely turn off the backlight when we go to level 0 */
	if (dcon->bl_val == 0) {
		dcon->disp_mode &= ~MODE_BL_ENABLE;
		dcon_write(dcon, DCON_REG_MODE, dcon->disp_mode);
	} else if (!(dcon->disp_mode & MODE_BL_ENABLE)) {
		dcon->disp_mode |= MODE_BL_ENABLE;
		dcon_write(dcon, DCON_REG_MODE, dcon->disp_mode);
	}
}