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
struct nvkm_sec2 {int /*<<< orphan*/  engine; int /*<<< orphan*/  work; int /*<<< orphan*/  addr; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nvkm_sec2* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nvkm_engine_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_sec2 ; 
 int /*<<< orphan*/  nvkm_sec2_recv ; 

int
nvkm_sec2_new_(struct nvkm_device *device, int index, u32 addr,
	       struct nvkm_sec2 **psec2)
{
	struct nvkm_sec2 *sec2;

	if (!(sec2 = *psec2 = kzalloc(sizeof(*sec2), GFP_KERNEL)))
		return -ENOMEM;
	sec2->addr = addr;
	INIT_WORK(&sec2->work, nvkm_sec2_recv);

	return nvkm_engine_ctor(&nvkm_sec2, device, index, true, &sec2->engine);
}