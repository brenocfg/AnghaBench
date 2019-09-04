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
struct nvkm_device {int chipset; } ;
struct nvkm_clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g84_clk ; 
 int nv50_clk_new_ (int /*<<< orphan*/ *,struct nvkm_device*,int,int,struct nvkm_clk**) ; 

int
g84_clk_new(struct nvkm_device *device, int index, struct nvkm_clk **pclk)
{
	return nv50_clk_new_(&g84_clk, device, index,
			     (device->chipset >= 0x94), pclk);
}