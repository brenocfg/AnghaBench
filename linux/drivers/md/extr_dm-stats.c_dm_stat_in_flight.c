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
struct dm_stat_shared {int /*<<< orphan*/ * in_flight; } ;

/* Variables and functions */
 size_t READ ; 
 size_t WRITE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dm_stat_in_flight(struct dm_stat_shared *shared)
{
	return atomic_read(&shared->in_flight[READ]) +
	       atomic_read(&shared->in_flight[WRITE]);
}