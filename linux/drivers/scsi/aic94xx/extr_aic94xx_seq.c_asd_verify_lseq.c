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
typedef  int /*<<< orphan*/  const u8 ;
typedef  int u32 ;
struct asd_ha_struct {int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_DPRINTK (char*,int,int) ; 
 int LSEQ_CODEPAGE_SIZE ; 
 int /*<<< orphan*/  LmBISTCTL1 (int) ; 
 int LmRAMPAGE_LSHIFT ; 
 scalar_t__ LmSEQRAM (int) ; 
 int /*<<< orphan*/  asd_printk (char*,int /*<<< orphan*/ ,int,int,int) ; 
 int asd_read_reg_dword (struct asd_ha_struct*,scalar_t__) ; 
 int /*<<< orphan*/  asd_write_reg_dword (struct asd_ha_struct*,int /*<<< orphan*/ ,int) ; 
 int le32_to_cpu (int const) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asd_verify_lseq(struct asd_ha_struct *asd_ha, const u8 *_prog,
			   u32 size, int lseq)
{
#define LSEQ_CODEPAGE_SIZE 4096
	int pages =  (size + LSEQ_CODEPAGE_SIZE - 1) / LSEQ_CODEPAGE_SIZE;
	u32 page;
	const u32 *prog = (u32 *) _prog;

	for (page = 0; page < pages; page++) {
		u32 i;

		asd_write_reg_dword(asd_ha, LmBISTCTL1(lseq),
				    page << LmRAMPAGE_LSHIFT);
		for (i = 0; size > 0 && i < LSEQ_CODEPAGE_SIZE;
		     i += 4, prog++, size-=4) {

			u32 val = asd_read_reg_dword(asd_ha, LmSEQRAM(lseq)+i);

			if (le32_to_cpu(*prog) != val) {
				asd_printk("%s: LSEQ%d verify failed "
					   "page:%d, offs:%d\n",
					   pci_name(asd_ha->pcidev),
					   lseq, page, i);
				return -1;
			}
		}
	}
	ASD_DPRINTK("LSEQ%d verified %d bytes, passed\n", lseq,
		    (int)((u8 *)prog-_prog));
	return 0;
}