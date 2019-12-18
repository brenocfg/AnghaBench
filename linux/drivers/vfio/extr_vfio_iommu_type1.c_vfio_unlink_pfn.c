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
struct vfio_pfn {int /*<<< orphan*/  node; } ;
struct vfio_dma {int /*<<< orphan*/  pfn_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vfio_unlink_pfn(struct vfio_dma *dma, struct vfio_pfn *old)
{
	rb_erase(&old->node, &dma->pfn_list);
}