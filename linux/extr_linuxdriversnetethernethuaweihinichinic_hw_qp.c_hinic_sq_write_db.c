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
typedef  int u16 ;
struct hinic_wq {int wqebb_size; } ;
struct hinic_sq {struct hinic_wq* wq; } ;

/* Variables and functions */
 int ALIGN (unsigned int,int) ; 
 int /*<<< orphan*/  SQ_DB_ADDR (struct hinic_sq*,int) ; 
 int /*<<< orphan*/  sq_prepare_db (struct hinic_sq*,int,unsigned int) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hinic_sq_write_db(struct hinic_sq *sq, u16 prod_idx, unsigned int wqe_size,
		       unsigned int cos)
{
	struct hinic_wq *wq = sq->wq;

	/* increment prod_idx to the next */
	prod_idx += ALIGN(wqe_size, wq->wqebb_size) / wq->wqebb_size;

	wmb();  /* Write all before the doorbell */

	writel(sq_prepare_db(sq, prod_idx, cos), SQ_DB_ADDR(sq, prod_idx));
}