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
typedef  int u32 ;
struct nvkm_object {int dummy; } ;
struct nv20_gr_chan {int chid; int /*<<< orphan*/  inst; struct nv20_gr* gr; } ;
struct nv20_gr {int /*<<< orphan*/  ctxtab; } ;

/* Variables and functions */
 struct nv20_gr_chan* nv20_gr_chan (struct nvkm_object*) ; 
 int /*<<< orphan*/  nvkm_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_kmap (int /*<<< orphan*/ ) ; 
 int nvkm_memory_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_wo32 (int /*<<< orphan*/ ,int,int) ; 

int
nv20_gr_chan_init(struct nvkm_object *object)
{
	struct nv20_gr_chan *chan = nv20_gr_chan(object);
	struct nv20_gr *gr = chan->gr;
	u32 inst = nvkm_memory_addr(chan->inst);

	nvkm_kmap(gr->ctxtab);
	nvkm_wo32(gr->ctxtab, chan->chid * 4, inst >> 4);
	nvkm_done(gr->ctxtab);
	return 0;
}