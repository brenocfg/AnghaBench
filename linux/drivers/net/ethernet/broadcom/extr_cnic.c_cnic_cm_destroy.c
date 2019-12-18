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
struct cnic_sock {scalar_t__ flags; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SK_F_INUSE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  cnic_cm_cleanup (struct cnic_sock*) ; 
 int /*<<< orphan*/  cnic_in_use (struct cnic_sock*) ; 
 int /*<<< orphan*/  csk_hold (struct cnic_sock*) ; 
 int /*<<< orphan*/  csk_put (struct cnic_sock*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 

__attribute__((used)) static int cnic_cm_destroy(struct cnic_sock *csk)
{
	if (!cnic_in_use(csk))
		return -EINVAL;

	csk_hold(csk);
	clear_bit(SK_F_INUSE, &csk->flags);
	smp_mb__after_atomic();
	while (atomic_read(&csk->ref_count) != 1)
		msleep(1);
	cnic_cm_cleanup(csk);

	csk->flags = 0;
	csk_put(csk);
	return 0;
}