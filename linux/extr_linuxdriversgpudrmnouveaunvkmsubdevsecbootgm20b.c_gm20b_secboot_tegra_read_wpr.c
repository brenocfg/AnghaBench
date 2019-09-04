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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  subdev; } ;
struct gm200_secboot {TYPE_1__ base; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  nvkm_error (int /*<<< orphan*/ *,char*) ; 

int
gm20b_secboot_tegra_read_wpr(struct gm200_secboot *gsb, u32 mc_base)
{
	nvkm_error(&gsb->base.subdev, "Tegra support not compiled in\n");
	return -EINVAL;
}