#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_object {int dummy; } ;
struct TYPE_4__ {int user; } ;
struct nv50_disp_chan {TYPE_2__ chid; TYPE_1__* disp; } ;
struct TYPE_3__ {int /*<<< orphan*/  ramht; } ;

/* Variables and functions */
 int nvkm_ramht_insert (int /*<<< orphan*/ ,struct nvkm_object*,int,int,int /*<<< orphan*/ ,int) ; 

int
gf119_disp_dmac_bind(struct nv50_disp_chan *chan,
		     struct nvkm_object *object, u32 handle)
{
	return nvkm_ramht_insert(chan->disp->ramht, object,
				 chan->chid.user, -9, handle,
				 chan->chid.user << 27 | 0x00000001);
}