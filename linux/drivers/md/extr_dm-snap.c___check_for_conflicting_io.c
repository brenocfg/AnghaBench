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
struct dm_snapshot {int dummy; } ;
typedef  int /*<<< orphan*/  chunk_t ;

/* Variables and functions */
 scalar_t__ __chunk_is_tracked (struct dm_snapshot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void __check_for_conflicting_io(struct dm_snapshot *s, chunk_t chunk)
{
	while (__chunk_is_tracked(s, chunk))
		msleep(1);
}