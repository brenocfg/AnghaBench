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
struct TYPE_2__ {void (* pause ) (struct nvkm_fifo*,unsigned long*) ;} ;

/* Variables and functions */
 void stub1 (struct nvkm_fifo*,unsigned long*) ; 

void
nvkm_fifo_pause(struct nvkm_fifo *fifo, unsigned long *flags)
{
	return fifo->func->pause(fifo, flags);
}