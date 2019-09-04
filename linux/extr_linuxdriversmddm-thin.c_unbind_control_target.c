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
struct pool {struct dm_target* ti; } ;
struct dm_target {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void unbind_control_target(struct pool *pool, struct dm_target *ti)
{
	if (pool->ti == ti)
		pool->ti = NULL;
}