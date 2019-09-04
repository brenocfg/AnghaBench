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
typedef  int u64 ;
struct nvkm_fifo {int nr; TYPE_1__* func; } ;
struct nvkm_engine {int dummy; } ;
struct TYPE_2__ {int (* info ) (struct nvkm_fifo*,int,int*) ;} ;

/* Variables and functions */
 int ENOSYS ; 
#define  NV_DEVICE_FIFO_CHANNELS 128 
 struct nvkm_fifo* nvkm_fifo (struct nvkm_engine*) ; 
 int stub1 (struct nvkm_fifo*,int,int*) ; 

__attribute__((used)) static int
nvkm_fifo_info(struct nvkm_engine *engine, u64 mthd, u64 *data)
{
	struct nvkm_fifo *fifo = nvkm_fifo(engine);
	switch (mthd) {
	case NV_DEVICE_FIFO_CHANNELS: *data = fifo->nr; return 0;
	default:
		if (fifo->func->info)
			return fifo->func->info(fifo, mthd, data);
		break;
	}
	return -ENOSYS;
}