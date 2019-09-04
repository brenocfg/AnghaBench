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
typedef  scalar_t__ uint32_t ;
struct cx23885_dev {TYPE_1__* pci; int /*<<< orphan*/  need_dma_reset; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_REQ ; 
 int /*<<< orphan*/  TC_REQ_SET ; 
 int /*<<< orphan*/  VBI_B_DMA ; 
 int /*<<< orphan*/  VBI_C_DMA ; 
 int /*<<< orphan*/  VID_B_DMA ; 
 int /*<<< orphan*/  VID_C_DMA ; 
 scalar_t__ cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void cx23885_clear_bridge_error(struct cx23885_dev *dev)
{
	uint32_t reg1_val, reg2_val;

	if (!dev->need_dma_reset)
		return;

	reg1_val = cx_read(TC_REQ); /* read-only */
	reg2_val = cx_read(TC_REQ_SET);

	if (reg1_val && reg2_val) {
		cx_write(TC_REQ, reg1_val);
		cx_write(TC_REQ_SET, reg2_val);
		cx_read(VID_B_DMA);
		cx_read(VBI_B_DMA);
		cx_read(VID_C_DMA);
		cx_read(VBI_C_DMA);

		dev_info(&dev->pci->dev,
			"dma in progress detected 0x%08x 0x%08x, clearing\n",
			reg1_val, reg2_val);
	}
}