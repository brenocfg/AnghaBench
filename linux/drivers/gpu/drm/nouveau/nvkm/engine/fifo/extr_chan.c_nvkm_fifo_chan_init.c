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
struct nvkm_object {int dummy; } ;
struct nvkm_fifo_chan {TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init ) (struct nvkm_fifo_chan*) ;} ;

/* Variables and functions */
 struct nvkm_fifo_chan* nvkm_fifo_chan (struct nvkm_object*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_fifo_chan*) ; 

__attribute__((used)) static int
nvkm_fifo_chan_init(struct nvkm_object *object)
{
	struct nvkm_fifo_chan *chan = nvkm_fifo_chan(object);
	chan->func->init(chan);
	return 0;
}