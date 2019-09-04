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
typedef  int /*<<< orphan*/  u64 ;
struct platform_device {int dummy; } ;
struct nvkm_device_tegra_func {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 

int
nvkm_device_tegra_new(const struct nvkm_device_tegra_func *func,
		      struct platform_device *pdev,
		      const char *cfg, const char *dbg,
		      bool detect, bool mmio, u64 subdev_mask,
		      struct nvkm_device **pdevice)
{
	return -ENOSYS;
}