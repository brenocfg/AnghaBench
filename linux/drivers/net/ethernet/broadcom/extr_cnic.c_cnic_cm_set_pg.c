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
 int /*<<< orphan*/  SK_F_PG_OFFLD_COMPLETE ; 
 int /*<<< orphan*/  cnic_cm_offload_pg (struct cnic_sock*) ; 
 int /*<<< orphan*/  cnic_cm_update_pg (struct cnic_sock*) ; 
 scalar_t__ cnic_offld_prep (struct cnic_sock*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cnic_cm_set_pg(struct cnic_sock *csk)
{
	if (cnic_offld_prep(csk)) {
		if (test_bit(SK_F_PG_OFFLD_COMPLETE, &csk->flags))
			cnic_cm_update_pg(csk);
		else
			cnic_cm_offload_pg(csk);
	}
	return 0;
}