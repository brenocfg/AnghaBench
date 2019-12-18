#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ib_qp_security {int error_comps_pending; int destroying; int /*<<< orphan*/  mutex; TYPE_1__* ports_pkeys; int /*<<< orphan*/  error_complete; } ;
struct TYPE_2__ {int /*<<< orphan*/  alt; int /*<<< orphan*/  main; } ;

/* Variables and functions */
 int check_qp_port_pkey_settings (TYPE_1__*,struct ib_qp_security*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  port_pkey_list_insert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qp_to_error (struct ib_qp_security*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void ib_destroy_qp_security_abort(struct ib_qp_security *sec)
{
	int ret;
	int i;

	/* Return if not IB */
	if (!sec)
		return;

	/* If a concurrent cache update is in progress this
	 * QP security could be marked for an error state
	 * transition.  Wait for this to complete.
	 */
	for (i = 0; i < sec->error_comps_pending; i++)
		wait_for_completion(&sec->error_complete);

	mutex_lock(&sec->mutex);
	sec->destroying = false;

	/* Restore the position in the lists and verify
	 * access is still allowed in case a cache update
	 * occurred while attempting to destroy.
	 *
	 * Because these setting were listed already
	 * and removed during ib_destroy_qp_security_begin
	 * we know the pkey_index_qp_list for the PKey
	 * already exists so port_pkey_list_insert won't fail.
	 */
	if (sec->ports_pkeys) {
		port_pkey_list_insert(&sec->ports_pkeys->main);
		port_pkey_list_insert(&sec->ports_pkeys->alt);
	}

	ret = check_qp_port_pkey_settings(sec->ports_pkeys, sec);
	if (ret)
		qp_to_error(sec);

	mutex_unlock(&sec->mutex);
}