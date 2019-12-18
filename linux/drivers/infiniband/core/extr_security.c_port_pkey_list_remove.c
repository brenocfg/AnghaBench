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
struct pkey_index_qp_list {int /*<<< orphan*/  qp_list_lock; } ;
struct ib_port_pkey {scalar_t__ state; int /*<<< orphan*/  qp_list; } ;

/* Variables and functions */
 scalar_t__ IB_PORT_PKEY_LISTED ; 
 scalar_t__ IB_PORT_PKEY_VALID ; 
 struct pkey_index_qp_list* get_pkey_idx_qp_list (struct ib_port_pkey*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void port_pkey_list_remove(struct ib_port_pkey *pp)
{
	struct pkey_index_qp_list *pkey;

	if (pp->state != IB_PORT_PKEY_LISTED)
		return;

	pkey = get_pkey_idx_qp_list(pp);

	spin_lock(&pkey->qp_list_lock);
	list_del(&pp->qp_list);
	spin_unlock(&pkey->qp_list_lock);

	/* The setting may still be valid, i.e. after
	 * a destroy has failed for example.
	 */
	pp->state = IB_PORT_PKEY_VALID;
}