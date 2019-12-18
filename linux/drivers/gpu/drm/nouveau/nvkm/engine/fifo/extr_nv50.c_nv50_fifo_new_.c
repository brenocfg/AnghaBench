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
struct nvkm_fifo_func {int dummy; } ;
struct nvkm_fifo {int /*<<< orphan*/  mask; } ;
struct nvkm_device {int dummy; } ;
struct nv50_fifo {struct nvkm_fifo base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nv50_fifo* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nvkm_fifo_ctor (struct nvkm_fifo_func const*,struct nvkm_device*,int,int,struct nvkm_fifo*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

int
nv50_fifo_new_(const struct nvkm_fifo_func *func, struct nvkm_device *device,
	       int index, struct nvkm_fifo **pfifo)
{
	struct nv50_fifo *fifo;
	int ret;

	if (!(fifo = kzalloc(sizeof(*fifo), GFP_KERNEL)))
		return -ENOMEM;
	*pfifo = &fifo->base;

	ret = nvkm_fifo_ctor(func, device, index, 128, &fifo->base);
	if (ret)
		return ret;

	set_bit(0, fifo->base.mask); /* PIO channel */
	set_bit(127, fifo->base.mask); /* inactive channel */
	return 0;
}