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
struct nvkm_secboot {int dummy; } ;
struct gm200_secboot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA186_MC_BASE ; 
 struct gm200_secboot* gm200_secboot (struct nvkm_secboot*) ; 
 int gm200_secboot_oneinit (struct nvkm_secboot*) ; 
 int gm20b_secboot_tegra_read_wpr (struct gm200_secboot*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gp10b_secboot_oneinit(struct nvkm_secboot *sb)
{
	struct gm200_secboot *gsb = gm200_secboot(sb);
	int ret;

	ret = gm20b_secboot_tegra_read_wpr(gsb, TEGRA186_MC_BASE);
	if (ret)
		return ret;

	return gm200_secboot_oneinit(sb);
}