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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {scalar_t__ dmabounce; } ;
struct device {TYPE_1__ archdata; } ;
struct TYPE_4__ {int (* dma_supported ) (struct device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_2__ arm_dma_ops ; 
 int stub1 (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmabounce_dma_supported(struct device *dev, u64 dma_mask)
{
	if (dev->archdata.dmabounce)
		return 0;

	return arm_dma_ops.dma_supported(dev, dma_mask);
}