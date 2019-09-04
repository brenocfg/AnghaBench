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
struct nvkm_device {int dummy; } ;
struct nvkm_clk {int dummy; } ;
struct gk104_clk {struct nvkm_clk base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  gk104_clk ; 
 struct gk104_clk* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nvkm_clk_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int,struct nvkm_clk*) ; 

int
gk104_clk_new(struct nvkm_device *device, int index, struct nvkm_clk **pclk)
{
	struct gk104_clk *clk;

	if (!(clk = kzalloc(sizeof(*clk), GFP_KERNEL)))
		return -ENOMEM;
	*pclk = &clk->base;

	return nvkm_clk_ctor(&gk104_clk, device, index, true, &clk->base);
}