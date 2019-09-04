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
typedef  int uint32_t ;
struct mtd_info {int dummy; } ;
struct denali_nand_info {int /*<<< orphan*/  (* host_write ) (struct denali_nand_info*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int DENALI_BANK (struct denali_nand_info*) ; 
 int /*<<< orphan*/  DENALI_ERASE ; 
 int DENALI_MAP10 ; 
 int EIO ; 
 int INTR__ERASE_COMP ; 
 int INTR__ERASE_FAIL ; 
 int /*<<< orphan*/  denali_reset_irq (struct denali_nand_info*) ; 
 int denali_wait_for_irq (struct denali_nand_info*,int) ; 
 struct denali_nand_info* mtd_to_denali (struct mtd_info*) ; 
 int /*<<< orphan*/  stub1 (struct denali_nand_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int denali_erase(struct mtd_info *mtd, int page)
{
	struct denali_nand_info *denali = mtd_to_denali(mtd);
	uint32_t irq_status;

	denali_reset_irq(denali);

	denali->host_write(denali, DENALI_MAP10 | DENALI_BANK(denali) | page,
			   DENALI_ERASE);

	/* wait for erase to complete or failure to occur */
	irq_status = denali_wait_for_irq(denali,
					 INTR__ERASE_COMP | INTR__ERASE_FAIL);

	return irq_status & INTR__ERASE_COMP ? 0 : -EIO;
}