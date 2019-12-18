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
struct vmd_dev {TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* resource; } ;
struct TYPE_3__ {int /*<<< orphan*/ * child; } ;

/* Variables and functions */
 size_t VMD_MEMBAR1 ; 
 size_t VMD_MEMBAR2 ; 

__attribute__((used)) static void vmd_detach_resources(struct vmd_dev *vmd)
{
	vmd->dev->resource[VMD_MEMBAR1].child = NULL;
	vmd->dev->resource[VMD_MEMBAR2].child = NULL;
}