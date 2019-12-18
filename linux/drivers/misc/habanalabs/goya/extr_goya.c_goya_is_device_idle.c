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
typedef  int u64 ;
typedef  int u32 ;
struct seq_file {int dummy; } ;
struct hl_device {int dummy; } ;

/* Variables and functions */
 int DMA_MAX_NUM ; 
 int GOYA_ENGINE_ID_DMA_0 ; 
 int GOYA_ENGINE_ID_MME_0 ; 
 int GOYA_ENGINE_ID_TPC_0 ; 
 scalar_t__ IS_DMA_IDLE (int) ; 
 scalar_t__ IS_DMA_QM_IDLE (int) ; 
 scalar_t__ IS_MME_CMDQ_IDLE (int) ; 
 scalar_t__ IS_MME_IDLE (int) ; 
 scalar_t__ IS_MME_QM_IDLE (int) ; 
 scalar_t__ IS_TPC_CMDQ_IDLE (int) ; 
 scalar_t__ IS_TPC_IDLE (int) ; 
 scalar_t__ IS_TPC_QM_IDLE (int) ; 
 int RREG32 (int) ; 
 int TPC_MAX_NUM ; 
 int mmDMA_CH_0_STS0 ; 
 int mmDMA_QM_0_GLBL_STS0 ; 
 int mmDMA_QM_1_GLBL_STS0 ; 
 int mmMME_ARCH_STATUS ; 
 int mmMME_CMDQ_GLBL_STS0 ; 
 int mmMME_QM_GLBL_STS0 ; 
 int mmTPC0_CFG_STATUS ; 
 int mmTPC0_CMDQ_GLBL_STS0 ; 
 int mmTPC0_QM_GLBL_STS0 ; 
 int mmTPC1_QM_GLBL_STS0 ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char const*,int,char*,int,int,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static bool goya_is_device_idle(struct hl_device *hdev, u32 *mask,
				struct seq_file *s)
{
	const char *fmt = "%-5d%-9s%#-14x%#-16x%#x\n";
	const char *dma_fmt = "%-5d%-9s%#-14x%#x\n";
	u32 qm_glbl_sts0, cmdq_glbl_sts0, dma_core_sts0, tpc_cfg_sts,
		mme_arch_sts;
	bool is_idle = true, is_eng_idle;
	u64 offset;
	int i;

	if (s)
		seq_puts(s, "\nDMA  is_idle  QM_GLBL_STS0  DMA_CORE_STS0\n"
				"---  -------  ------------  -------------\n");

	offset = mmDMA_QM_1_GLBL_STS0 - mmDMA_QM_0_GLBL_STS0;

	for (i = 0 ; i < DMA_MAX_NUM ; i++) {
		qm_glbl_sts0 = RREG32(mmDMA_QM_0_GLBL_STS0 + i * offset);
		dma_core_sts0 = RREG32(mmDMA_CH_0_STS0 + i * offset);
		is_eng_idle = IS_DMA_QM_IDLE(qm_glbl_sts0) &&
				IS_DMA_IDLE(dma_core_sts0);
		is_idle &= is_eng_idle;

		if (mask)
			*mask |= !is_eng_idle << (GOYA_ENGINE_ID_DMA_0 + i);
		if (s)
			seq_printf(s, dma_fmt, i, is_eng_idle ? "Y" : "N",
					qm_glbl_sts0, dma_core_sts0);
	}

	if (s)
		seq_puts(s,
			"\nTPC  is_idle  QM_GLBL_STS0  CMDQ_GLBL_STS0  CFG_STATUS\n"
			"---  -------  ------------  --------------  ----------\n");

	offset = mmTPC1_QM_GLBL_STS0 - mmTPC0_QM_GLBL_STS0;

	for (i = 0 ; i < TPC_MAX_NUM ; i++) {
		qm_glbl_sts0 = RREG32(mmTPC0_QM_GLBL_STS0 + i * offset);
		cmdq_glbl_sts0 = RREG32(mmTPC0_CMDQ_GLBL_STS0 + i * offset);
		tpc_cfg_sts = RREG32(mmTPC0_CFG_STATUS + i * offset);
		is_eng_idle = IS_TPC_QM_IDLE(qm_glbl_sts0) &&
				IS_TPC_CMDQ_IDLE(cmdq_glbl_sts0) &&
				IS_TPC_IDLE(tpc_cfg_sts);
		is_idle &= is_eng_idle;

		if (mask)
			*mask |= !is_eng_idle << (GOYA_ENGINE_ID_TPC_0 + i);
		if (s)
			seq_printf(s, fmt, i, is_eng_idle ? "Y" : "N",
				qm_glbl_sts0, cmdq_glbl_sts0, tpc_cfg_sts);
	}

	if (s)
		seq_puts(s,
			"\nMME  is_idle  QM_GLBL_STS0  CMDQ_GLBL_STS0  ARCH_STATUS\n"
			"---  -------  ------------  --------------  -----------\n");

	qm_glbl_sts0 = RREG32(mmMME_QM_GLBL_STS0);
	cmdq_glbl_sts0 = RREG32(mmMME_CMDQ_GLBL_STS0);
	mme_arch_sts = RREG32(mmMME_ARCH_STATUS);
	is_eng_idle = IS_MME_QM_IDLE(qm_glbl_sts0) &&
			IS_MME_CMDQ_IDLE(cmdq_glbl_sts0) &&
			IS_MME_IDLE(mme_arch_sts);
	is_idle &= is_eng_idle;

	if (mask)
		*mask |= !is_eng_idle << GOYA_ENGINE_ID_MME_0;
	if (s) {
		seq_printf(s, fmt, 0, is_eng_idle ? "Y" : "N", qm_glbl_sts0,
				cmdq_glbl_sts0, mme_arch_sts);
		seq_puts(s, "\n");
	}

	return is_idle;
}