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
typedef  int /*<<< orphan*/  u32 ;
struct rxe_dev {int /*<<< orphan*/  ah_pool; } ;
struct rxe_ah {int /*<<< orphan*/  av; int /*<<< orphan*/  pelem; } ;
struct rdma_ah_attr {int dummy; } ;
struct ib_udata {int dummy; } ;
struct ib_ah {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int rxe_add_to_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rxe_av_chk_attr (struct rxe_dev*,struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rxe_init_av (struct rdma_ah_attr*,int /*<<< orphan*/ *) ; 
 struct rxe_ah* to_rah (struct ib_ah*) ; 
 struct rxe_dev* to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rxe_create_ah(struct ib_ah *ibah, struct rdma_ah_attr *attr,
			 u32 flags, struct ib_udata *udata)

{
	int err;
	struct rxe_dev *rxe = to_rdev(ibah->device);
	struct rxe_ah *ah = to_rah(ibah);

	err = rxe_av_chk_attr(rxe, attr);
	if (err)
		return err;

	err = rxe_add_to_pool(&rxe->ah_pool, &ah->pelem);
	if (err)
		return err;

	rxe_init_av(attr, &ah->av);
	return 0;
}