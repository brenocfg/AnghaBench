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
struct dma_desc {int /*<<< orphan*/  des3; int /*<<< orphan*/  des2; } ;

/* Variables and functions */
 int XGMAC_TDES2_B1L ; 
 unsigned int XGMAC_TDES3_CIC ; 
 int XGMAC_TDES3_CIC_SHIFT ; 
 unsigned int XGMAC_TDES3_FD ; 
 unsigned int XGMAC_TDES3_FL ; 
 unsigned int XGMAC_TDES3_LD ; 
 unsigned int XGMAC_TDES3_OWN ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwxgmac2_prepare_tx_desc(struct dma_desc *p, int is_fs, int len,
				     bool csum_flag, int mode, bool tx_own,
				     bool ls, unsigned int tot_pkt_len)
{
	unsigned int tdes3 = le32_to_cpu(p->des3);

	p->des2 |= cpu_to_le32(len & XGMAC_TDES2_B1L);

	tdes3 |= tot_pkt_len & XGMAC_TDES3_FL;
	if (is_fs)
		tdes3 |= XGMAC_TDES3_FD;
	else
		tdes3 &= ~XGMAC_TDES3_FD;

	if (csum_flag)
		tdes3 |= 0x3 << XGMAC_TDES3_CIC_SHIFT;
	else
		tdes3 &= ~XGMAC_TDES3_CIC;

	if (ls)
		tdes3 |= XGMAC_TDES3_LD;
	else
		tdes3 &= ~XGMAC_TDES3_LD;

	/* Finally set the OWN bit. Later the DMA will start! */
	if (tx_own)
		tdes3 |= XGMAC_TDES3_OWN;

	if (is_fs && tx_own)
		/* When the own bit, for the first frame, has to be set, all
		 * descriptors for the same frame has to be set before, to
		 * avoid race condition.
		 */
		dma_wmb();

	p->des3 = cpu_to_le32(tdes3);
}