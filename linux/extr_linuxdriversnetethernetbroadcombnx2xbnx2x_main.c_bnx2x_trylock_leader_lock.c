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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2x_get_leader_lock_resource (struct bnx2x*) ; 
 int bnx2x_trylock_hw_lock (struct bnx2x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bnx2x_trylock_leader_lock(struct bnx2x *bp)
{
	return bnx2x_trylock_hw_lock(bp, bnx2x_get_leader_lock_resource(bp));
}