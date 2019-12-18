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
struct rxe_dev {int dummy; } ;
struct rxe_ah {int /*<<< orphan*/  av; } ;
struct rdma_ah_attr {int dummy; } ;
struct ib_ah {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int rxe_av_chk_attr (struct rxe_dev*,struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rxe_init_av (struct rdma_ah_attr*,int /*<<< orphan*/ *) ; 
 struct rxe_ah* to_rah (struct ib_ah*) ; 
 struct rxe_dev* to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rxe_modify_ah(struct ib_ah *ibah, struct rdma_ah_attr *attr)
{
	int err;
	struct rxe_dev *rxe = to_rdev(ibah->device);
	struct rxe_ah *ah = to_rah(ibah);

	err = rxe_av_chk_attr(rxe, attr);
	if (err)
		return err;

	rxe_init_av(attr, &ah->av);
	return 0;
}