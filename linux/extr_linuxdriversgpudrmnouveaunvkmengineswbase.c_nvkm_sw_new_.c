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
struct nvkm_sw_func {int dummy; } ;
struct nvkm_sw {int /*<<< orphan*/  engine; struct nvkm_sw_func const* func; int /*<<< orphan*/  chan; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct nvkm_sw* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nvkm_engine_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_sw ; 

int
nvkm_sw_new_(const struct nvkm_sw_func *func, struct nvkm_device *device,
	     int index, struct nvkm_sw **psw)
{
	struct nvkm_sw *sw;

	if (!(sw = *psw = kzalloc(sizeof(*sw), GFP_KERNEL)))
		return -ENOMEM;
	INIT_LIST_HEAD(&sw->chan);
	sw->func = func;

	return nvkm_engine_ctor(&nvkm_sw, device, index, true, &sw->engine);
}