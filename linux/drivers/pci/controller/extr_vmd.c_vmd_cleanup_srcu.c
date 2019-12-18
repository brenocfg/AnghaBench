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
struct vmd_dev {int msix_count; TYPE_1__* irqs; } ;
struct TYPE_2__ {int /*<<< orphan*/  srcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_srcu_struct (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmd_cleanup_srcu(struct vmd_dev *vmd)
{
	int i;

	for (i = 0; i < vmd->msix_count; i++)
		cleanup_srcu_struct(&vmd->irqs[i].srcu);
}