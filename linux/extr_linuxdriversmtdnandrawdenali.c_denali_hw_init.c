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
struct denali_nand_info {int oob_skip_bytes; scalar_t__ reg; scalar_t__ revision; } ;

/* Variables and functions */
 scalar_t__ CHIP_ENABLE_DONT_CARE ; 
 int CHIP_EN_DONT_CARE__FLAG ; 
 int DENALI_DEFAULT_OOB_SKIP_BYTES ; 
 scalar_t__ RB_PIN_ENABLED ; 
 scalar_t__ REVISION ; 
 scalar_t__ SPARE_AREA_MARKER ; 
 scalar_t__ SPARE_AREA_SKIP_BYTES ; 
 int /*<<< orphan*/  denali_detect_max_banks (struct denali_nand_info*) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 scalar_t__ swab16 (int) ; 

__attribute__((used)) static void denali_hw_init(struct denali_nand_info *denali)
{
	/*
	 * The REVISION register may not be reliable.  Platforms are allowed to
	 * override it.
	 */
	if (!denali->revision)
		denali->revision = swab16(ioread32(denali->reg + REVISION));

	/*
	 * Set how many bytes should be skipped before writing data in OOB.
	 * If a non-zero value has already been set (by firmware or something),
	 * just use it.  Otherwise, set the driver default.
	 */
	denali->oob_skip_bytes = ioread32(denali->reg + SPARE_AREA_SKIP_BYTES);
	if (!denali->oob_skip_bytes) {
		denali->oob_skip_bytes = DENALI_DEFAULT_OOB_SKIP_BYTES;
		iowrite32(denali->oob_skip_bytes,
			  denali->reg + SPARE_AREA_SKIP_BYTES);
	}

	denali_detect_max_banks(denali);
	iowrite32(0x0F, denali->reg + RB_PIN_ENABLED);
	iowrite32(CHIP_EN_DONT_CARE__FLAG, denali->reg + CHIP_ENABLE_DONT_CARE);

	iowrite32(0xffff, denali->reg + SPARE_AREA_MARKER);
}