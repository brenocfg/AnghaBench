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
struct nvkm_fifo {TYPE_1__* func; } ;
struct nvkm_fault_data {int dummy; } ;
struct TYPE_2__ {void (* fault ) (struct nvkm_fifo*,struct nvkm_fault_data*) ;} ;

/* Variables and functions */
 void stub1 (struct nvkm_fifo*,struct nvkm_fault_data*) ; 

void
nvkm_fifo_fault(struct nvkm_fifo *fifo, struct nvkm_fault_data *info)
{
	return fifo->func->fault(fifo, info);
}