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
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct nvkm_fb {TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_wr32 (int /*<<< orphan*/ ,int,int) ; 

void
nv41_fb_init(struct nvkm_fb *fb)
{
	nvkm_wr32(fb->subdev.device, 0x100800, 0x00000001);
}