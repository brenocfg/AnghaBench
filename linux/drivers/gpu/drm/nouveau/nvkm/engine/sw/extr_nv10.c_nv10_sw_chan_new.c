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
struct nvkm_object {int dummy; } ;
struct nvkm_sw_chan {struct nvkm_object object; } ;
struct nvkm_sw {int dummy; } ;
struct nvkm_oclass {int dummy; } ;
struct nvkm_fifo_chan {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_sw_chan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv10_sw_chan ; 
 int nvkm_sw_chan_ctor (int /*<<< orphan*/ *,struct nvkm_sw*,struct nvkm_fifo_chan*,struct nvkm_oclass const*,struct nvkm_sw_chan*) ; 

__attribute__((used)) static int
nv10_sw_chan_new(struct nvkm_sw *sw, struct nvkm_fifo_chan *fifo,
		 const struct nvkm_oclass *oclass, struct nvkm_object **pobject)
{
	struct nvkm_sw_chan *chan;

	if (!(chan = kzalloc(sizeof(*chan), GFP_KERNEL)))
		return -ENOMEM;
	*pobject = &chan->object;

	return nvkm_sw_chan_ctor(&nv10_sw_chan, sw, fifo, oclass, chan);
}