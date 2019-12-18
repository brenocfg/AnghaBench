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
struct nvkm_sw_chan {int dummy; } ;
struct nvkm_oclass {int dummy; } ;
struct nvkm_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv04_nvsw ; 
 int nvkm_nvsw_new_ (int /*<<< orphan*/ *,struct nvkm_sw_chan*,struct nvkm_oclass const*,void*,int /*<<< orphan*/ ,struct nvkm_object**) ; 

__attribute__((used)) static int
nv04_nvsw_new(struct nvkm_sw_chan *chan, const struct nvkm_oclass *oclass,
	      void *data, u32 size, struct nvkm_object **pobject)
{
	return nvkm_nvsw_new_(&nv04_nvsw, chan, oclass, data, size, pobject);
}