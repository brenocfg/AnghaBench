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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct nvkm_falcon {TYPE_1__* func; int /*<<< orphan*/  user; int /*<<< orphan*/  secret; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* load_imem ) (struct nvkm_falcon*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_falcon*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
nvkm_falcon_load_imem(struct nvkm_falcon *falcon, void *data, u32 start,
		      u32 size, u16 tag, u8 port, bool secure)
{
	if (secure && !falcon->secret) {
		nvkm_warn(falcon->user,
			  "writing with secure tag on a non-secure falcon!\n");
		return;
	}

	falcon->func->load_imem(falcon, data, start, size, tag, port,
				secure);
}