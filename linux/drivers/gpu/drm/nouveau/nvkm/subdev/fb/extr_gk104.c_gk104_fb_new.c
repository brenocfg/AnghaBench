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
struct nvkm_fb {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int gf100_fb_new_ (int /*<<< orphan*/ *,struct nvkm_device*,int,struct nvkm_fb**) ; 
 int /*<<< orphan*/  gk104_fb ; 

int
gk104_fb_new(struct nvkm_device *device, int index, struct nvkm_fb **pfb)
{
	return gf100_fb_new_(&gk104_fb, device, index, pfb);
}