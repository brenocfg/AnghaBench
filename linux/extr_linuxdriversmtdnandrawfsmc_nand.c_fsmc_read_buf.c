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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct mtd_info {int dummy; } ;
struct fsmc_nand_data {int /*<<< orphan*/  data_va; } ;

/* Variables and functions */
 scalar_t__ IS_ALIGNED (int,int) ; 
 struct fsmc_nand_data* mtd_to_fsmc (struct mtd_info*) ; 
 int /*<<< orphan*/  readb_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl_relaxed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsmc_read_buf(struct mtd_info *mtd, uint8_t *buf, int len)
{
	struct fsmc_nand_data *host  = mtd_to_fsmc(mtd);
	int i;

	if (IS_ALIGNED((uintptr_t)buf, sizeof(uint32_t)) &&
			IS_ALIGNED(len, sizeof(uint32_t))) {
		uint32_t *p = (uint32_t *)buf;
		len = len >> 2;
		for (i = 0; i < len; i++)
			p[i] = readl_relaxed(host->data_va);
	} else {
		for (i = 0; i < len; i++)
			buf[i] = readb_relaxed(host->data_va);
	}
}