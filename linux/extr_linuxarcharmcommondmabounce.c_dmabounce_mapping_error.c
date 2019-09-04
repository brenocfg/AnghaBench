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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int (* mapping_error ) (struct device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__ arm_dma_ops ; 
 int stub1 (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmabounce_mapping_error(struct device *dev, dma_addr_t dma_addr)
{
	return arm_dma_ops.mapping_error(dev, dma_addr);
}