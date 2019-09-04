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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u32 ;
struct mtd_info {int dummy; } ;
struct denali_nand_info {int /*<<< orphan*/  (* host_read ) (struct denali_nand_info*,int) ;} ;

/* Variables and functions */
 int DENALI_BANK (struct denali_nand_info*) ; 
 int DENALI_MAP11_DATA ; 
 struct denali_nand_info* mtd_to_denali (struct mtd_info*) ; 
 int /*<<< orphan*/  stub1 (struct denali_nand_info*,int) ; 

__attribute__((used)) static void denali_read_buf16(struct mtd_info *mtd, uint8_t *buf, int len)
{
	struct denali_nand_info *denali = mtd_to_denali(mtd);
	u32 addr = DENALI_MAP11_DATA | DENALI_BANK(denali);
	uint16_t *buf16 = (uint16_t *)buf;
	int i;

	for (i = 0; i < len / 2; i++)
		buf16[i] = denali->host_read(denali, addr);
}