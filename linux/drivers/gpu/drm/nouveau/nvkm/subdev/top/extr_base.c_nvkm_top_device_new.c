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
struct nvkm_top_device {int fault; int engine; int runlist; int reset; int intr; int /*<<< orphan*/  head; scalar_t__ addr; int /*<<< orphan*/  index; } ;
struct nvkm_top {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVKM_SUBDEV_NR ; 
 struct nvkm_top_device* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct nvkm_top_device *
nvkm_top_device_new(struct nvkm_top *top)
{
	struct nvkm_top_device *info = kmalloc(sizeof(*info), GFP_KERNEL);
	if (info) {
		info->index = NVKM_SUBDEV_NR;
		info->addr = 0;
		info->fault = -1;
		info->engine = -1;
		info->runlist = -1;
		info->reset = -1;
		info->intr = -1;
		list_add_tail(&info->head, &top->device);
	}
	return info;
}