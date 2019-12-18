#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct TYPE_2__ {int rings_per_vf; } ;
struct octeon_device {TYPE_1__ sriov_info; } ;

/* Variables and functions */
 int CN23XX_VF_IQ_OFFSET ; 
 int CN23XX_VF_OQ_OFFSET ; 
 int CN23XX_VF_SLI_IQ_BASE_ADDR64 (int) ; 
 int CN23XX_VF_SLI_IQ_DOORBELL (int) ; 
 int CN23XX_VF_SLI_IQ_INSTR_COUNT64 (int) ; 
 int CN23XX_VF_SLI_IQ_PKT_CONTROL64 (int) ; 
 int CN23XX_VF_SLI_IQ_SIZE (int) ; 
 int CN23XX_VF_SLI_OQ_BASE_ADDR64 (int) ; 
 int CN23XX_VF_SLI_OQ_BUFF_INFO_SIZE (int) ; 
 int CN23XX_VF_SLI_OQ_PKTS_CREDIT (int) ; 
 int CN23XX_VF_SLI_OQ_PKTS_SENT (int) ; 
 int CN23XX_VF_SLI_OQ_PKT_CONTROL (int) ; 
 int CN23XX_VF_SLI_OQ_PKT_INT_LEVELS (int) ; 
 int CN23XX_VF_SLI_OQ_SIZE (int) ; 
 scalar_t__ octeon_read_csr64 (struct octeon_device*,int) ; 
 scalar_t__ sprintf (char*,char*,...) ; 

__attribute__((used)) static int cn23xx_vf_read_csr_reg(char *s, struct octeon_device *oct)
{
	int len = 0;
	u32 reg;
	int i;

	/* PCI  Window Registers */

	len += sprintf(s + len, "\n\t Octeon CSR Registers\n\n");

	for (i = 0; i < (oct->sriov_info.rings_per_vf); i++) {
		reg = CN23XX_VF_SLI_OQ_BUFF_INFO_SIZE(i);
		len += sprintf(s + len,
			       "\n[%08x] (SLI_PKT%d_OUT_SIZE): %016llx\n",
			       reg, i, (u64)octeon_read_csr64(oct, reg));
	}

	for (i = 0; i < (oct->sriov_info.rings_per_vf); i++) {
		reg = CN23XX_VF_SLI_IQ_INSTR_COUNT64(i);
		len += sprintf(s + len,
			       "\n[%08x] (SLI_PKT_IN_DONE%d_CNTS): %016llx\n",
			       reg, i, (u64)octeon_read_csr64(oct, reg));
	}

	for (i = 0; i < (oct->sriov_info.rings_per_vf); i++) {
		reg = CN23XX_VF_SLI_OQ_PKTS_CREDIT(i);
		len += sprintf(s + len,
			       "\n[%08x] (SLI_PKT%d_SLIST_BAOFF_DBELL): %016llx\n",
			       reg, i, (u64)octeon_read_csr64(oct, reg));
	}

	for (i = 0; i < (oct->sriov_info.rings_per_vf); i++) {
		reg = CN23XX_VF_SLI_OQ_SIZE(i);
		len += sprintf(s + len,
			       "\n[%08x] (SLI_PKT%d_SLIST_FIFO_RSIZE): %016llx\n",
			       reg, i, (u64)octeon_read_csr64(oct, reg));
	}

	for (i = 0; i < (oct->sriov_info.rings_per_vf); i++) {
		reg = CN23XX_VF_SLI_OQ_PKT_CONTROL(i);
		len += sprintf(s + len,
			       "\n[%08x] (SLI_PKT%d__OUTPUT_CONTROL): %016llx\n",
			       reg, i, (u64)octeon_read_csr64(oct, reg));
	}

	for (i = 0; i < (oct->sriov_info.rings_per_vf); i++) {
		reg = CN23XX_VF_SLI_OQ_BASE_ADDR64(i);
		len += sprintf(s + len,
			       "\n[%08x] (SLI_PKT%d_SLIST_BADDR): %016llx\n",
			       reg, i, (u64)octeon_read_csr64(oct, reg));
	}

	for (i = 0; i < (oct->sriov_info.rings_per_vf); i++) {
		reg = CN23XX_VF_SLI_OQ_PKT_INT_LEVELS(i);
		len += sprintf(s + len,
			       "\n[%08x] (SLI_PKT%d_INT_LEVELS): %016llx\n",
			       reg, i, (u64)octeon_read_csr64(oct, reg));
	}

	for (i = 0; i < (oct->sriov_info.rings_per_vf); i++) {
		reg = CN23XX_VF_SLI_OQ_PKTS_SENT(i);
		len += sprintf(s + len, "\n[%08x] (SLI_PKT%d_CNTS): %016llx\n",
			       reg, i, (u64)octeon_read_csr64(oct, reg));
	}

	for (i = 0; i < (oct->sriov_info.rings_per_vf); i++) {
		reg = 0x100c0 + i * CN23XX_VF_OQ_OFFSET;
		len += sprintf(s + len,
			       "\n[%08x] (SLI_PKT%d_ERROR_INFO): %016llx\n",
			       reg, i, (u64)octeon_read_csr64(oct, reg));
	}

	for (i = 0; i < (oct->sriov_info.rings_per_vf); i++) {
		reg = 0x100d0 + i * CN23XX_VF_IQ_OFFSET;
		len += sprintf(s + len,
			       "\n[%08x] (SLI_PKT%d_VF_INT_SUM): %016llx\n",
			       reg, i, (u64)octeon_read_csr64(oct, reg));
	}

	for (i = 0; i < (oct->sriov_info.rings_per_vf); i++) {
		reg = CN23XX_VF_SLI_IQ_PKT_CONTROL64(i);
		len += sprintf(s + len,
			       "\n[%08x] (SLI_PKT%d_INPUT_CONTROL): %016llx\n",
			       reg, i, (u64)octeon_read_csr64(oct, reg));
	}

	for (i = 0; i < (oct->sriov_info.rings_per_vf); i++) {
		reg = CN23XX_VF_SLI_IQ_BASE_ADDR64(i);
		len += sprintf(s + len,
			       "\n[%08x] (SLI_PKT%d_INSTR_BADDR): %016llx\n",
			       reg, i, (u64)octeon_read_csr64(oct, reg));
	}

	for (i = 0; i < (oct->sriov_info.rings_per_vf); i++) {
		reg = CN23XX_VF_SLI_IQ_DOORBELL(i);
		len += sprintf(s + len,
			       "\n[%08x] (SLI_PKT%d_INSTR_BAOFF_DBELL): %016llx\n",
			       reg, i, (u64)octeon_read_csr64(oct, reg));
	}

	for (i = 0; i < (oct->sriov_info.rings_per_vf); i++) {
		reg = CN23XX_VF_SLI_IQ_SIZE(i);
		len += sprintf(s + len,
			       "\n[%08x] (SLI_PKT%d_INSTR_FIFO_RSIZE): %016llx\n",
			       reg, i, (u64)octeon_read_csr64(oct, reg));
	}

	for (i = 0; i < (oct->sriov_info.rings_per_vf); i++) {
		reg = CN23XX_VF_SLI_IQ_INSTR_COUNT64(i);
		len += sprintf(s + len,
			       "\n[%08x] (SLI_PKT_IN_DONE%d_CNTS): %016llx\n",
			       reg, i, (u64)octeon_read_csr64(oct, reg));
	}

	return len;
}