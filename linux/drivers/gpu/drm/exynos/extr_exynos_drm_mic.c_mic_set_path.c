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
struct exynos_mic {int /*<<< orphan*/  dev; int /*<<< orphan*/  sysreg; scalar_t__ i80_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DSD_CFG_MUX ; 
 unsigned int MIC0_I80_MUX ; 
 unsigned int MIC0_ON_MUX ; 
 unsigned int MIC0_RGB_MUX ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void mic_set_path(struct exynos_mic *mic, bool enable)
{
	int ret;
	unsigned int val;

	ret = regmap_read(mic->sysreg, DSD_CFG_MUX, &val);
	if (ret) {
		DRM_DEV_ERROR(mic->dev,
			      "mic: Failed to read system register\n");
		return;
	}

	if (enable) {
		if (mic->i80_mode)
			val |= MIC0_I80_MUX;
		else
			val |= MIC0_RGB_MUX;

		val |=  MIC0_ON_MUX;
	} else
		val &= ~(MIC0_RGB_MUX | MIC0_I80_MUX | MIC0_ON_MUX);

	ret = regmap_write(mic->sysreg, DSD_CFG_MUX, val);
	if (ret)
		DRM_DEV_ERROR(mic->dev,
			      "mic: Failed to read system register\n");
}