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
struct siw_qp {int /*<<< orphan*/  ref; } ;
struct siw_device {int /*<<< orphan*/  qp_xa; } ;

/* Variables and functions */
 scalar_t__ kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct siw_qp* xa_load (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline struct siw_qp *siw_qp_id2obj(struct siw_device *sdev, int id)
{
	struct siw_qp *qp;

	rcu_read_lock();
	qp = xa_load(&sdev->qp_xa, id);
	if (likely(qp && kref_get_unless_zero(&qp->ref))) {
		rcu_read_unlock();
		return qp;
	}
	rcu_read_unlock();
	return NULL;
}