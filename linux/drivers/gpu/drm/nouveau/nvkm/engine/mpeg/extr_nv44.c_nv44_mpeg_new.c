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
struct nvkm_engine {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct nv44_mpeg {struct nvkm_engine engine; int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct nv44_mpeg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv44_mpeg ; 
 int nvkm_engine_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int,struct nvkm_engine*) ; 

int
nv44_mpeg_new(struct nvkm_device *device, int index, struct nvkm_engine **pmpeg)
{
	struct nv44_mpeg *mpeg;

	if (!(mpeg = kzalloc(sizeof(*mpeg), GFP_KERNEL)))
		return -ENOMEM;
	INIT_LIST_HEAD(&mpeg->chan);
	*pmpeg = &mpeg->engine;

	return nvkm_engine_ctor(&nv44_mpeg, device, index, true, &mpeg->engine);
}