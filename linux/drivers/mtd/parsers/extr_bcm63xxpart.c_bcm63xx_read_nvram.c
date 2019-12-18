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
typedef  int /*<<< orphan*/  u32 ;
struct mtd_info {int dummy; } ;
struct bcm963xx_nvram {scalar_t__ psi_size; } ;

/* Variables and functions */
 scalar_t__ BCM963XX_DEFAULT_PSI_SIZE ; 
 int /*<<< orphan*/  BCM963XX_NVRAM_OFFSET ; 
 int /*<<< orphan*/  BCM963XX_NVRAM_V5_SIZE ; 
 int bcm963xx_nvram_checksum (struct bcm963xx_nvram*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mtd_read (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,void*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm63xx_read_nvram(struct mtd_info *master,
	struct bcm963xx_nvram *nvram)
{
	u32 actual_crc, expected_crc;
	size_t retlen;
	int ret;

	/* extract nvram data */
	ret = mtd_read(master, BCM963XX_NVRAM_OFFSET, BCM963XX_NVRAM_V5_SIZE,
			&retlen, (void *)nvram);
	if (ret)
		return ret;

	ret = bcm963xx_nvram_checksum(nvram, &expected_crc, &actual_crc);
	if (ret)
		pr_warn("nvram checksum failed, contents may be invalid (expected %08x, got %08x)\n",
			expected_crc, actual_crc);

	if (!nvram->psi_size)
		nvram->psi_size = BCM963XX_DEFAULT_PSI_SIZE;

	return 0;
}