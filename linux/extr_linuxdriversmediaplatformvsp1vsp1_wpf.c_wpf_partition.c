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
struct vsp1_pipeline {int dummy; } ;
struct vsp1_partition_window {int dummy; } ;
struct vsp1_partition {struct vsp1_partition_window wpf; } ;
struct vsp1_entity {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void wpf_partition(struct vsp1_entity *entity,
			  struct vsp1_pipeline *pipe,
			  struct vsp1_partition *partition,
			  unsigned int partition_idx,
			  struct vsp1_partition_window *window)
{
	partition->wpf = *window;
}