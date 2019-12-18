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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_nvsw {int /*<<< orphan*/  chan; } ;
struct nv04_sw_chan {int /*<<< orphan*/  ref; } ;
struct nv04_nvsw_get_ref_v0 {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct nv04_sw_chan* nv04_sw_chan (int /*<<< orphan*/ ) ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct nv04_nvsw_get_ref_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nv04_nvsw_mthd_get_ref(struct nvkm_nvsw *nvsw, void *data, u32 size)
{
	struct nv04_sw_chan *chan = nv04_sw_chan(nvsw->chan);
	union {
		struct nv04_nvsw_get_ref_v0 v0;
	} *args = data;
	int ret = -ENOSYS;

	if (!(ret = nvif_unpack(ret, &data, &size, args->v0, 0, 0, false))) {
		args->v0.ref = atomic_read(&chan->ref);
	}

	return ret;
}