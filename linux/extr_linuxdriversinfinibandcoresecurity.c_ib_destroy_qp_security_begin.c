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
struct ib_qp_security {int destroying; int /*<<< orphan*/  mutex; int /*<<< orphan*/  error_list_count; int /*<<< orphan*/  error_comps_pending; TYPE_1__* ports_pkeys; } ;
struct TYPE_2__ {int /*<<< orphan*/  alt; int /*<<< orphan*/  main; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  port_pkey_list_remove (int /*<<< orphan*/ *) ; 

void ib_destroy_qp_security_begin(struct ib_qp_security *sec)
{
	/* Return if not IB */
	if (!sec)
		return;

	mutex_lock(&sec->mutex);

	/* Remove the QP from the lists so it won't get added to
	 * a to_error_list during the destroy process.
	 */
	if (sec->ports_pkeys) {
		port_pkey_list_remove(&sec->ports_pkeys->main);
		port_pkey_list_remove(&sec->ports_pkeys->alt);
	}

	/* If the QP is already in one or more of those lists
	 * the destroying flag will ensure the to error flow
	 * doesn't operate on an undefined QP.
	 */
	sec->destroying = true;

	/* Record the error list count to know how many completions
	 * to wait for.
	 */
	sec->error_comps_pending = atomic_read(&sec->error_list_count);

	mutex_unlock(&sec->mutex);
}