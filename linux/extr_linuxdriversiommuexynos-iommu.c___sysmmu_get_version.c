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
typedef  int u32 ;
struct sysmmu_drvdata {int /*<<< orphan*/  version; int /*<<< orphan*/  sysmmu; scalar_t__ sfrbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAKE_MMU_VER (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMU_MAJ_VER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMU_MIN_VER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMU_RAW_VER (int) ; 
 scalar_t__ REG_MMU_VERSION ; 
 int /*<<< orphan*/  __sysmmu_disable_clocks (struct sysmmu_drvdata*) ; 
 int /*<<< orphan*/  __sysmmu_enable_clocks (struct sysmmu_drvdata*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void __sysmmu_get_version(struct sysmmu_drvdata *data)
{
	u32 ver;

	__sysmmu_enable_clocks(data);

	ver = readl(data->sfrbase + REG_MMU_VERSION);

	/* controllers on some SoCs don't report proper version */
	if (ver == 0x80000001u)
		data->version = MAKE_MMU_VER(1, 0);
	else
		data->version = MMU_RAW_VER(ver);

	dev_dbg(data->sysmmu, "hardware version: %d.%d\n",
		MMU_MAJ_VER(data->version), MMU_MIN_VER(data->version));

	__sysmmu_disable_clocks(data);
}