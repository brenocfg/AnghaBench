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
struct siw_qp {struct ib_qp* ib_qp; } ;
struct ib_qp {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 struct siw_qp* siw_qp_id2obj (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  siw_qp_put (struct siw_qp*) ; 
 int /*<<< orphan*/  to_siw_dev (struct ib_device*) ; 

__attribute__((used)) static struct ib_qp *siw_get_base_qp(struct ib_device *base_dev, int id)
{
	struct siw_qp *qp = siw_qp_id2obj(to_siw_dev(base_dev), id);

	if (qp) {
		/*
		 * siw_qp_id2obj() increments object reference count
		 */
		siw_qp_put(qp);
		return qp->ib_qp;
	}
	return NULL;
}