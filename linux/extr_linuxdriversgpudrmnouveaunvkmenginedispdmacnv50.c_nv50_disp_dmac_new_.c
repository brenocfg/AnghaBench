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
typedef  int /*<<< orphan*/  u64 ;
struct nvkm_oclass {struct nvkm_client* client; } ;
struct nvkm_object {int dummy; } ;
struct nvkm_client {int dummy; } ;
struct nv50_disp_chan_mthd {int dummy; } ;
struct nv50_disp_chan_func {int dummy; } ;
struct nv50_disp_chan {int push; int /*<<< orphan*/  memory; } ;
struct nv50_disp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
#define  NVKM_MEM_TARGET_HOST 130 
#define  NVKM_MEM_TARGET_NCOH 129 
#define  NVKM_MEM_TARGET_VRAM 128 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct nv50_disp_chan* nv50_disp_chan (struct nvkm_object*) ; 
 int nv50_disp_chan_new_ (struct nv50_disp_chan_func const*,struct nv50_disp_chan_mthd const*,struct nv50_disp*,int,int,int,struct nvkm_oclass const*,struct nvkm_object**) ; 
 int nvkm_memory_addr (int /*<<< orphan*/ ) ; 
 int nvkm_memory_size (int /*<<< orphan*/ ) ; 
 int nvkm_memory_target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_umem_search (struct nvkm_client*,int /*<<< orphan*/ ) ; 

int
nv50_disp_dmac_new_(const struct nv50_disp_chan_func *func,
		    const struct nv50_disp_chan_mthd *mthd,
		    struct nv50_disp *disp, int chid, int head, u64 push,
		    const struct nvkm_oclass *oclass,
		    struct nvkm_object **pobject)
{
	struct nvkm_client *client = oclass->client;
	struct nv50_disp_chan *chan;
	int ret;

	ret = nv50_disp_chan_new_(func, mthd, disp, chid, chid, head, oclass,
				  pobject);
	chan = nv50_disp_chan(*pobject);
	if (ret)
		return ret;

	chan->memory = nvkm_umem_search(client, push);
	if (IS_ERR(chan->memory))
		return PTR_ERR(chan->memory);

	if (nvkm_memory_size(chan->memory) < 0x1000)
		return -EINVAL;

	switch (nvkm_memory_target(chan->memory)) {
	case NVKM_MEM_TARGET_VRAM: chan->push = 0x00000001; break;
	case NVKM_MEM_TARGET_NCOH: chan->push = 0x00000002; break;
	case NVKM_MEM_TARGET_HOST: chan->push = 0x00000003; break;
	default:
		return -EINVAL;
	}

	chan->push |= nvkm_memory_addr(chan->memory) >> 8;
	return 0;
}