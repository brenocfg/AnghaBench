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
struct denali_nand_info {int /*<<< orphan*/  (* host_write ) (struct denali_nand_info*,int,int /*<<< orphan*/  const) ;} ;

/* Variables and functions */
 int DENALI_BANK (struct denali_nand_info*) ; 
 int DENALI_MAP11_DATA ; 
 struct denali_nand_info* mtd_to_denali (struct mtd_info*) ; 
 int /*<<< orphan*/  stub1 (struct denali_nand_info*,int,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void denali_write_buf16(struct mtd_info *mtd, const uint8_t *buf,
			       int len)
{
	struct denali_nand_info *denali = mtd_to_denali(mtd);
	u32 addr = DENALI_MAP11_DATA | DENALI_BANK(denali);
	const uint16_t *buf16 = (const uint16_t *)buf;
	int i;

	for (i = 0; i < len / 2; i++)
		denali->host_write(denali, addr, buf16[i]);
}