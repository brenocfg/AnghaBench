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
struct dma_device {int dev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_ida ; 
 int ida_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_dma_id(struct dma_device *device)
{
	int rc = ida_alloc(&dma_ida, GFP_KERNEL);

	if (rc < 0)
		return rc;
	device->dev_id = rc;
	return 0;
}