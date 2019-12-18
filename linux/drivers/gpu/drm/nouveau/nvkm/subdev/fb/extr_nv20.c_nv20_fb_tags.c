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
typedef  scalar_t__ const u32 ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct nvkm_fb {TYPE_1__ subdev; } ;

/* Variables and functions */
 scalar_t__ const nvkm_rd32 (int /*<<< orphan*/ ,int) ; 

u32
nv20_fb_tags(struct nvkm_fb *fb)
{
	const u32 tags = nvkm_rd32(fb->subdev.device, 0x100320);
	return tags ? tags + 1 : 0;
}