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
struct drm_device {scalar_t__ dev_private; } ;
typedef  int /*<<< orphan*/  drm_via_private_t ;

/* Variables and functions */
 int VIA_DMA_CSR_DD ; 
 int VIA_DMA_CSR_TD ; 
 scalar_t__ VIA_PCI_DMA_CSR0 ; 
 int /*<<< orphan*/  via_write (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static void
via_dmablit_engine_off(struct drm_device *dev, int engine)
{
	drm_via_private_t *dev_priv = (drm_via_private_t *)dev->dev_private;

	via_write(dev_priv, VIA_PCI_DMA_CSR0 + engine*0x04, VIA_DMA_CSR_TD | VIA_DMA_CSR_DD);
}