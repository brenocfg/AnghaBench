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
struct device_queue_manager {int sdma_bitmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ffs (int) ; 

__attribute__((used)) static int allocate_sdma_queue(struct device_queue_manager *dqm,
				unsigned int *sdma_queue_id)
{
	int bit;

	if (dqm->sdma_bitmap == 0)
		return -ENOMEM;

	bit = ffs(dqm->sdma_bitmap) - 1;
	dqm->sdma_bitmap &= ~(1 << bit);
	*sdma_queue_id = bit;

	return 0;
}