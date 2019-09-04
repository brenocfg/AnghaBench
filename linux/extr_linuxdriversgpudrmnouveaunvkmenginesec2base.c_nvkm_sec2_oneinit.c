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
struct TYPE_2__ {int /*<<< orphan*/  subdev; } ;
struct nvkm_sec2 {int /*<<< orphan*/  falcon; TYPE_1__ engine; } ;
struct nvkm_engine {int dummy; } ;

/* Variables and functions */
 int nvkm_falcon_v1_new (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 struct nvkm_sec2* nvkm_sec2 (struct nvkm_engine*) ; 

__attribute__((used)) static int
nvkm_sec2_oneinit(struct nvkm_engine *engine)
{
	struct nvkm_sec2 *sec2 = nvkm_sec2(engine);
	return nvkm_falcon_v1_new(&sec2->engine.subdev, "SEC2", 0x87000,
				  &sec2->falcon);
}