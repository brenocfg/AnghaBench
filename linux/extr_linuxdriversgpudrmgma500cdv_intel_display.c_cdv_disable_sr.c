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
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_BLC_SELF ; 
 int FW_BLC_SELF_EN ; 
 int /*<<< orphan*/  OV_OVADD ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gma_wait_for_vblank (struct drm_device*) ; 

void cdv_disable_sr(struct drm_device *dev)
{
	if (REG_READ(FW_BLC_SELF) & FW_BLC_SELF_EN) {

		/* Disable self-refresh before adjust WM */
		REG_WRITE(FW_BLC_SELF, (REG_READ(FW_BLC_SELF) & ~FW_BLC_SELF_EN));
		REG_READ(FW_BLC_SELF);

		gma_wait_for_vblank(dev);

		/* Cedarview workaround to write ovelay plane, which force to leave
		 * MAX_FIFO state.
		 */
		REG_WRITE(OV_OVADD, 0/*dev_priv->ovl_offset*/);
		REG_READ(OV_OVADD);

		gma_wait_for_vblank(dev);
	}

}