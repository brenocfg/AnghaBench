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
struct cec_notifier {int /*<<< orphan*/  lock; scalar_t__ cec_adap; int /*<<< orphan*/  phys_addr; int /*<<< orphan*/  conn_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_PHYS_ADDR_INVALID ; 
 int /*<<< orphan*/  cec_notifier_put (struct cec_notifier*) ; 
 int /*<<< orphan*/  cec_phys_addr_invalidate (scalar_t__) ; 
 int /*<<< orphan*/  cec_s_conn_info (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void cec_notifier_conn_unregister(struct cec_notifier *n)
{
	if (!n)
		return;

	mutex_lock(&n->lock);
	memset(&n->conn_info, 0, sizeof(n->conn_info));
	n->phys_addr = CEC_PHYS_ADDR_INVALID;
	if (n->cec_adap) {
		cec_phys_addr_invalidate(n->cec_adap);
		cec_s_conn_info(n->cec_adap, NULL);
	}
	mutex_unlock(&n->lock);
	cec_notifier_put(n);
}