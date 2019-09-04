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
struct dma_chunk {int /*<<< orphan*/  len; scalar_t__ bus_addr; TYPE_2__* region; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_id; int /*<<< orphan*/  bus_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  kfree (struct dma_chunk*) ; 
 int lv1_unmap_device_dma_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dma_sb_free_chunk(struct dma_chunk *c)
{
	int result = 0;

	if (c->bus_addr) {
		result = lv1_unmap_device_dma_region(c->region->dev->bus_id,
			c->region->dev->dev_id, c->bus_addr, c->len);
		BUG_ON(result);
	}

	kfree(c);
	return result;
}