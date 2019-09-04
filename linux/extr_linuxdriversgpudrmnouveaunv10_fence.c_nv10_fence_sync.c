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
struct nouveau_fence {int dummy; } ;
struct nouveau_channel {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static int
nv10_fence_sync(struct nouveau_fence *fence,
		struct nouveau_channel *prev, struct nouveau_channel *chan)
{
	return -ENODEV;
}