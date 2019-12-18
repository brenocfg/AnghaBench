#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int irq_pending_mask; } ;
typedef  TYPE_1__ drm_via_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  VIA_REG_INTERRUPT ; 
 int via_read (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  via_write (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline__ void viadrv_acknowledge_irqs(drm_via_private_t *dev_priv)
{
	u32 status;

	if (dev_priv) {
		/* Acknowledge interrupts */
		status = via_read(dev_priv, VIA_REG_INTERRUPT);
		via_write(dev_priv, VIA_REG_INTERRUPT, status |
			  dev_priv->irq_pending_mask);
	}
}