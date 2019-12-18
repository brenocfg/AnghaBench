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
struct slave {int dummy; } ;
struct bonding {int /*<<< orphan*/  mode_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tlb_clear_slave (struct bonding*,struct slave*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tlb_clear_slave(struct bonding *bond, struct slave *slave,
			 int save_load)
{
	spin_lock_bh(&bond->mode_lock);
	__tlb_clear_slave(bond, slave, save_load);
	spin_unlock_bh(&bond->mode_lock);
}