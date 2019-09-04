#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct drm_device {scalar_t__ dev_private; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  fence_queue; int /*<<< orphan*/  last_fence_retired; int /*<<< orphan*/  vbl_received; } ;
typedef  TYPE_1__ drm_mga_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  MGA_ICLEAR ; 
 int /*<<< orphan*/  MGA_PRIMADDRESS ; 
 int /*<<< orphan*/  MGA_PRIMEND ; 
 void* MGA_READ (int /*<<< orphan*/ ) ; 
 int MGA_SOFTRAPEN ; 
 int const MGA_SOFTRAPICLR ; 
 int /*<<< orphan*/  MGA_STATUS ; 
 int const MGA_VLINEICLR ; 
 int MGA_VLINEPEN ; 
 int /*<<< orphan*/  MGA_WRITE (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_handle_vblank (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

irqreturn_t mga_driver_irq_handler(int irq, void *arg)
{
	struct drm_device *dev = (struct drm_device *) arg;
	drm_mga_private_t *dev_priv = (drm_mga_private_t *) dev->dev_private;
	int status;
	int handled = 0;

	status = MGA_READ(MGA_STATUS);

	/* VBLANK interrupt */
	if (status & MGA_VLINEPEN) {
		MGA_WRITE(MGA_ICLEAR, MGA_VLINEICLR);
		atomic_inc(&dev_priv->vbl_received);
		drm_handle_vblank(dev, 0);
		handled = 1;
	}

	/* SOFTRAP interrupt */
	if (status & MGA_SOFTRAPEN) {
		const u32 prim_start = MGA_READ(MGA_PRIMADDRESS);
		const u32 prim_end = MGA_READ(MGA_PRIMEND);


		MGA_WRITE(MGA_ICLEAR, MGA_SOFTRAPICLR);

		/* In addition to clearing the interrupt-pending bit, we
		 * have to write to MGA_PRIMEND to re-start the DMA operation.
		 */
		if ((prim_start & ~0x03) != (prim_end & ~0x03))
			MGA_WRITE(MGA_PRIMEND, prim_end);

		atomic_inc(&dev_priv->last_fence_retired);
		wake_up(&dev_priv->fence_queue);
		handled = 1;
	}

	if (handled)
		return IRQ_HANDLED;
	return IRQ_NONE;
}