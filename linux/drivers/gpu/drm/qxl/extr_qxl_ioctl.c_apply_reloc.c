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
typedef  int /*<<< orphan*/  uint64_t ;
struct qxl_reloc_info {int dst_offset; int /*<<< orphan*/  dst_bo; int /*<<< orphan*/  src_offset; int /*<<< orphan*/  src_bo; } ;
struct qxl_device {int dummy; } ;

/* Variables and functions */
 int PAGE_MASK ; 
 void* qxl_bo_kmap_atomic_page (struct qxl_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qxl_bo_kunmap_atomic_page (struct qxl_device*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  qxl_bo_physical_address (struct qxl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
apply_reloc(struct qxl_device *qdev, struct qxl_reloc_info *info)
{
	void *reloc_page;

	reloc_page = qxl_bo_kmap_atomic_page(qdev, info->dst_bo, info->dst_offset & PAGE_MASK);
	*(uint64_t *)(reloc_page + (info->dst_offset & ~PAGE_MASK)) = qxl_bo_physical_address(qdev,
											      info->src_bo,
											      info->src_offset);
	qxl_bo_kunmap_atomic_page(qdev, info->dst_bo, reloc_page);
}