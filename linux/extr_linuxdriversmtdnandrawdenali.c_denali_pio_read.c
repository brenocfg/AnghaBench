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
typedef  int u32 ;
struct denali_nand_info {int caps; int /*<<< orphan*/  (* host_read ) (struct denali_nand_info*,int) ;} ;

/* Variables and functions */
 int DENALI_BANK (struct denali_nand_info*) ; 
 int DENALI_CAP_HW_ECC_FIXUP ; 
 int DENALI_MAP01 ; 
 int EBADMSG ; 
 int EIO ; 
 int INTR__ECC_ERR ; 
 int INTR__ECC_UNCOR_ERR ; 
 int INTR__ERASED_PAGE ; 
 int INTR__PAGE_XFER_INC ; 
 int /*<<< orphan*/  denali_reset_irq (struct denali_nand_info*) ; 
 int denali_wait_for_irq (struct denali_nand_info*,int) ; 
 int /*<<< orphan*/  memset (void*,int,size_t) ; 
 int /*<<< orphan*/  stub1 (struct denali_nand_info*,int) ; 

__attribute__((used)) static int denali_pio_read(struct denali_nand_info *denali, void *buf,
			   size_t size, int page, int raw)
{
	u32 addr = DENALI_MAP01 | DENALI_BANK(denali) | page;
	uint32_t *buf32 = (uint32_t *)buf;
	uint32_t irq_status, ecc_err_mask;
	int i;

	if (denali->caps & DENALI_CAP_HW_ECC_FIXUP)
		ecc_err_mask = INTR__ECC_UNCOR_ERR;
	else
		ecc_err_mask = INTR__ECC_ERR;

	denali_reset_irq(denali);

	for (i = 0; i < size / 4; i++)
		*buf32++ = denali->host_read(denali, addr);

	irq_status = denali_wait_for_irq(denali, INTR__PAGE_XFER_INC);
	if (!(irq_status & INTR__PAGE_XFER_INC))
		return -EIO;

	if (irq_status & INTR__ERASED_PAGE)
		memset(buf, 0xff, size);

	return irq_status & ecc_err_mask ? -EBADMSG : 0;
}