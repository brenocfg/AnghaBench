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
struct nvkm_sw_chan_sclass {int (* ctor ) (struct nvkm_sw_chan*,struct nvkm_oclass const*,void*,int /*<<< orphan*/ ,struct nvkm_object**) ;} ;
struct nvkm_sw_chan {int dummy; } ;
struct nvkm_oclass {struct nvkm_sw_chan_sclass* engn; int /*<<< orphan*/  parent; } ;
struct nvkm_object {int dummy; } ;

/* Variables and functions */
 struct nvkm_sw_chan* nvkm_sw_chan (int /*<<< orphan*/ ) ; 
 int stub1 (struct nvkm_sw_chan*,struct nvkm_oclass const*,void*,int /*<<< orphan*/ ,struct nvkm_object**) ; 

__attribute__((used)) static int
nvkm_sw_oclass_new(const struct nvkm_oclass *oclass, void *data, u32 size,
		   struct nvkm_object **pobject)
{
	struct nvkm_sw_chan *chan = nvkm_sw_chan(oclass->parent);
	const struct nvkm_sw_chan_sclass *sclass = oclass->engn;
	return sclass->ctor(chan, oclass, data, size, pobject);
}