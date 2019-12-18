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
typedef  int /*<<< orphan*/  u32 ;
struct mbo {int /*<<< orphan*/  bus_address; TYPE_1__* ifp; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* driver_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dma_alloc_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *dma_alloc(struct mbo *mbo, u32 size)
{
	struct device *dev = mbo->ifp->driver_dev;

	return dma_alloc_coherent(dev, size, &mbo->bus_address, GFP_KERNEL);
}