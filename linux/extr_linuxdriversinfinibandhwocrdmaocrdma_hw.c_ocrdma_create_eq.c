#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ocrdma_eqe {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct ocrdma_eq {TYPE_1__ q; struct ocrdma_dev* dev; } ;
struct ocrdma_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCRDMA_EQ_LEN ; 
 int ocrdma_alloc_q (struct ocrdma_dev*,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocrdma_free_q (struct ocrdma_dev*,TYPE_1__*) ; 
 int ocrdma_mbx_create_eq (struct ocrdma_dev*,struct ocrdma_eq*) ; 
 int /*<<< orphan*/  ocrdma_ring_eq_db (struct ocrdma_dev*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocrdma_create_eq(struct ocrdma_dev *dev,
			    struct ocrdma_eq *eq, u16 q_len)
{
	int status;

	status = ocrdma_alloc_q(dev, &eq->q, OCRDMA_EQ_LEN,
				sizeof(struct ocrdma_eqe));
	if (status)
		return status;

	status = ocrdma_mbx_create_eq(dev, eq);
	if (status)
		goto mbx_err;
	eq->dev = dev;
	ocrdma_ring_eq_db(dev, eq->q.id, true, true, 0);

	return 0;
mbx_err:
	ocrdma_free_q(dev, &eq->q);
	return status;
}