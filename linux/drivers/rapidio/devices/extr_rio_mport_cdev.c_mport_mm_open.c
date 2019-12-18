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
struct vm_area_struct {struct rio_mport_mapping* vm_private_data; } ;
struct rio_mport_mapping {int /*<<< orphan*/  ref; int /*<<< orphan*/  phys_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMAP ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmcd_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mport_mm_open(struct vm_area_struct *vma)
{
	struct rio_mport_mapping *map = vma->vm_private_data;

	rmcd_debug(MMAP, "%pad", &map->phys_addr);
	kref_get(&map->ref);
}