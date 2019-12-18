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
struct cnic_sock {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SK_F_CONNECT_START ; 
 int /*<<< orphan*/  SK_F_OFFLD_SCHED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cnic_offld_prep(struct cnic_sock *csk)
{
	if (test_and_set_bit(SK_F_OFFLD_SCHED, &csk->flags))
		return 0;

	if (!test_bit(SK_F_CONNECT_START, &csk->flags)) {
		clear_bit(SK_F_OFFLD_SCHED, &csk->flags);
		return 0;
	}

	return 1;
}