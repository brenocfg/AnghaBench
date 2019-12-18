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
struct sge_rspq {unsigned int iqe_len; unsigned int size; struct adapter* adap; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxgb4_set_rspq_intr_params (struct sge_rspq*,unsigned int,unsigned int) ; 

__attribute__((used)) static inline void init_rspq(struct adapter *adap, struct sge_rspq *q,
			     unsigned int us, unsigned int cnt,
			     unsigned int size, unsigned int iqe_size)
{
	q->adap = adap;
	cxgb4_set_rspq_intr_params(q, us, cnt);
	q->iqe_len = iqe_size;
	q->size = size;
}