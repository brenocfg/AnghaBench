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
struct nvkm_falcon {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  falcon_v1_wait_idle (struct nvkm_falcon*) ; 
 int /*<<< orphan*/  nvkm_falcon_wr32 (struct nvkm_falcon*,int,int) ; 

__attribute__((used)) static void
nvkm_falcon_v1_disable(struct nvkm_falcon *falcon)
{
	/* disable IRQs and wait for any previous code to complete */
	nvkm_falcon_wr32(falcon, 0x014, 0xff);
	falcon_v1_wait_idle(falcon);
}