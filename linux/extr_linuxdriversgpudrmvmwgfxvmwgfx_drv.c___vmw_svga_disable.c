#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* man; } ;
struct vmw_private {int /*<<< orphan*/  svga_lock; TYPE_2__ bdev; } ;
struct TYPE_3__ {int use_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVGA_REG_ENABLE ; 
 int SVGA_REG_ENABLE_ENABLE ; 
 int SVGA_REG_ENABLE_HIDE ; 
 size_t TTM_PL_VRAM ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_write (struct vmw_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __vmw_svga_disable(struct vmw_private *dev_priv)
{
	spin_lock(&dev_priv->svga_lock);
	if (dev_priv->bdev.man[TTM_PL_VRAM].use_type) {
		dev_priv->bdev.man[TTM_PL_VRAM].use_type = false;
		vmw_write(dev_priv, SVGA_REG_ENABLE,
			  SVGA_REG_ENABLE_HIDE |
			  SVGA_REG_ENABLE_ENABLE);
	}
	spin_unlock(&dev_priv->svga_lock);
}