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
struct pch_udc_dev {int dummy; } ;

/* Variables and functions */
 int DMA_DIR_RX ; 
 int DMA_DIR_TX ; 
 int /*<<< orphan*/  UDC_DEVCTL_ADDR ; 
 int /*<<< orphan*/  UDC_DEVCTL_RDE ; 
 int /*<<< orphan*/  UDC_DEVCTL_TDE ; 
 int /*<<< orphan*/  pch_udc_bit_clr (struct pch_udc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void pch_udc_clear_dma(struct pch_udc_dev *dev, int dir)
{
	if (dir == DMA_DIR_RX)
		pch_udc_bit_clr(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_RDE);
	else if (dir == DMA_DIR_TX)
		pch_udc_bit_clr(dev, UDC_DEVCTL_ADDR, UDC_DEVCTL_TDE);
}