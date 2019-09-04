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
struct rxe_pd {int dummy; } ;
struct rxe_dev {int /*<<< orphan*/  ah_pool; } ;
struct ib_ah {int dummy; } ;
struct rxe_ah {struct ib_ah ibah; int /*<<< orphan*/  av; struct rxe_pd* pd; } ;
struct rdma_ah_attr {int dummy; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ib_ah* ERR_PTR (int) ; 
 int /*<<< orphan*/  rxe_add_ref (struct rxe_pd*) ; 
 struct rxe_ah* rxe_alloc (int /*<<< orphan*/ *) ; 
 int rxe_av_chk_attr (struct rxe_dev*,struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rxe_init_av (struct rxe_dev*,struct rdma_ah_attr*,int /*<<< orphan*/ *) ; 
 struct rxe_dev* to_rdev (int /*<<< orphan*/ ) ; 
 struct rxe_pd* to_rpd (struct ib_pd*) ; 

__attribute__((used)) static struct ib_ah *rxe_create_ah(struct ib_pd *ibpd,
				   struct rdma_ah_attr *attr,
				   struct ib_udata *udata)

{
	int err;
	struct rxe_dev *rxe = to_rdev(ibpd->device);
	struct rxe_pd *pd = to_rpd(ibpd);
	struct rxe_ah *ah;

	err = rxe_av_chk_attr(rxe, attr);
	if (err)
		return ERR_PTR(err);

	ah = rxe_alloc(&rxe->ah_pool);
	if (!ah)
		return ERR_PTR(-ENOMEM);

	rxe_add_ref(pd);
	ah->pd = pd;

	rxe_init_av(rxe, attr, &ah->av);
	return &ah->ibah;
}