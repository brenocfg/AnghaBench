#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sge_rspq {int intr_params; } ;
struct TYPE_2__ {unsigned int* timer_val; } ;
struct adapter {TYPE_1__ sge; } ;

/* Variables and functions */
 unsigned int SGE_NTIMERS ; 

__attribute__((used)) static inline unsigned int qtimer_val(const struct adapter *adap,
				      const struct sge_rspq *q)
{
	unsigned int idx = q->intr_params >> 1;

	return idx < SGE_NTIMERS ? adap->sge.timer_val[idx] : 0;
}