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
struct md_cluster_info {int /*<<< orphan*/  state; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_CLUSTER_SEND_LOCK ; 
 int lock_token (struct md_cluster_info*,int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lock_comm(struct md_cluster_info *cinfo, bool mddev_locked)
{
	wait_event(cinfo->wait,
		   !test_and_set_bit(MD_CLUSTER_SEND_LOCK, &cinfo->state));

	return lock_token(cinfo, mddev_locked);
}