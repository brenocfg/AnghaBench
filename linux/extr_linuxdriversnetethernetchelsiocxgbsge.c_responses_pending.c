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
struct respQ_e {scalar_t__ GenerationBit; } ;
struct respQ {size_t cidx; scalar_t__ genbit; struct respQ_e* entries; } ;
struct adapter {TYPE_1__* sge; } ;
struct TYPE_2__ {struct respQ respQ; } ;

/* Variables and functions */

__attribute__((used)) static inline int responses_pending(const struct adapter *adapter)
{
	const struct respQ *Q = &adapter->sge->respQ;
	const struct respQ_e *e = &Q->entries[Q->cidx];

	return e->GenerationBit == Q->genbit;
}