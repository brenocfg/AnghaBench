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
struct vm_area_struct {int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; struct videobuf_mapping* vm_private_data; } ;
struct videobuf_mapping {int /*<<< orphan*/  count; TYPE_1__* q; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct videobuf_mapping*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void videobuf_vm_open(struct vm_area_struct *vma)
{
	struct videobuf_mapping *map = vma->vm_private_data;

	dev_dbg(map->q->dev, "vm_open %p [count=%u,vma=%08lx-%08lx]\n",
		map, map->count, vma->vm_start, vma->vm_end);

	map->count++;
}