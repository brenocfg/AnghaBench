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
struct t4_cqe {int dummy; } ;
struct t4_cq {scalar_t__ cidx; int size; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 scalar_t__ fill_cqe (struct sk_buff*,struct t4_cqe*,int,char*) ; 

__attribute__((used)) static int fill_hwcqes(struct sk_buff *msg, struct t4_cq *cq,
		       struct t4_cqe *cqes)
{
	u16 idx;

	idx = (cq->cidx > 0) ? cq->cidx - 1 : cq->size - 1;
	if (fill_cqe(msg, cqes, idx, "hwcq_idx"))
		goto err;
	idx = cq->cidx;
	if (fill_cqe(msg, cqes + 1, idx, "hwcq_idx"))
		goto err;

	return 0;
err:
	return -EMSGSIZE;
}