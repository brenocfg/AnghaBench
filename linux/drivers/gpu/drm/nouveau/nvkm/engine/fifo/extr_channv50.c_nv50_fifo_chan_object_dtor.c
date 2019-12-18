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
struct nvkm_fifo_chan {int dummy; } ;
struct nv50_fifo_chan {int /*<<< orphan*/  ramht; } ;

/* Variables and functions */
 struct nv50_fifo_chan* nv50_fifo_chan (struct nvkm_fifo_chan*) ; 
 int /*<<< orphan*/  nvkm_ramht_remove (int /*<<< orphan*/ ,int) ; 

void
nv50_fifo_chan_object_dtor(struct nvkm_fifo_chan *base, int cookie)
{
	struct nv50_fifo_chan *chan = nv50_fifo_chan(base);
	nvkm_ramht_remove(chan->ramht, cookie);
}