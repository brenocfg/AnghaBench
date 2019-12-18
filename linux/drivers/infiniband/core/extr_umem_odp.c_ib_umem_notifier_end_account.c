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
struct ib_umem_odp {scalar_t__ notifiers_count; int /*<<< orphan*/  umem_mutex; int /*<<< orphan*/  notifier_completion; int /*<<< orphan*/  notifiers_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ib_umem_notifier_end_account(struct ib_umem_odp *umem_odp)
{
	mutex_lock(&umem_odp->umem_mutex);
	/*
	 * This sequence increase will notify the QP page fault that the page
	 * that is going to be mapped in the spte could have been freed.
	 */
	++umem_odp->notifiers_seq;
	if (--umem_odp->notifiers_count == 0)
		complete_all(&umem_odp->notifier_completion);
	mutex_unlock(&umem_odp->umem_mutex);
}