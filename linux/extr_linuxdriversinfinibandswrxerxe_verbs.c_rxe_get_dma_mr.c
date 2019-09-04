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
struct ib_mr {int dummy; } ;
struct rxe_pd {struct ib_mr ibmr; } ;
struct rxe_mem {struct ib_mr ibmr; } ;
struct rxe_dev {int /*<<< orphan*/  mr_pool; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ib_mr* ERR_PTR (int) ; 
 int /*<<< orphan*/  rxe_add_index (struct rxe_pd*) ; 
 int /*<<< orphan*/  rxe_add_ref (struct rxe_pd*) ; 
 struct rxe_pd* rxe_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxe_drop_index (struct rxe_pd*) ; 
 int /*<<< orphan*/  rxe_drop_ref (struct rxe_pd*) ; 
 int rxe_mem_init_dma (struct rxe_pd*,int,struct rxe_pd*) ; 
 struct rxe_dev* to_rdev (int /*<<< orphan*/ ) ; 
 struct rxe_pd* to_rpd (struct ib_pd*) ; 

__attribute__((used)) static struct ib_mr *rxe_get_dma_mr(struct ib_pd *ibpd, int access)
{
	struct rxe_dev *rxe = to_rdev(ibpd->device);
	struct rxe_pd *pd = to_rpd(ibpd);
	struct rxe_mem *mr;
	int err;

	mr = rxe_alloc(&rxe->mr_pool);
	if (!mr) {
		err = -ENOMEM;
		goto err1;
	}

	rxe_add_index(mr);

	rxe_add_ref(pd);

	err = rxe_mem_init_dma(pd, access, mr);
	if (err)
		goto err2;

	return &mr->ibmr;

err2:
	rxe_drop_ref(pd);
	rxe_drop_index(mr);
	rxe_drop_ref(mr);
err1:
	return ERR_PTR(err);
}