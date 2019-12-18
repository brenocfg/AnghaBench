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
struct nv50_disp_chan {TYPE_1__* func; } ;
struct TYPE_2__ {int (* init ) (struct nv50_disp_chan*) ;int /*<<< orphan*/  (* intr ) (struct nv50_disp_chan*,int) ;} ;

/* Variables and functions */
 struct nv50_disp_chan* nv50_disp_chan (struct nvkm_object*) ; 
 int /*<<< orphan*/  stub1 (struct nv50_disp_chan*,int) ; 
 int stub2 (struct nv50_disp_chan*) ; 

__attribute__((used)) static int
nv50_disp_chan_init(struct nvkm_object *object)
{
	struct nv50_disp_chan *chan = nv50_disp_chan(object);
	chan->func->intr(chan, true);
	return chan->func->init(chan);
}