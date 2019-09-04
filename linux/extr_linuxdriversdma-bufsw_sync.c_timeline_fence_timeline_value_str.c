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
struct sync_timeline {int value; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 struct sync_timeline* dma_fence_parent (struct dma_fence*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void timeline_fence_timeline_value_str(struct dma_fence *fence,
					     char *str, int size)
{
	struct sync_timeline *parent = dma_fence_parent(fence);

	snprintf(str, size, "%d", parent->value);
}