#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  t6_up_cim_reg_array ;
typedef  int /*<<< orphan*/  t6_tp_tm_pio_array ;
typedef  int /*<<< orphan*/  t6_tp_pio_array ;
typedef  int /*<<< orphan*/  t6_tp_mib_index_array ;
typedef  int /*<<< orphan*/  t6_ma_ireg_array ;
typedef  int /*<<< orphan*/  t6_hma_ireg_array ;
typedef  int /*<<< orphan*/  t5_up_cim_reg_array ;
typedef  int /*<<< orphan*/  t5_tp_tm_pio_array ;
typedef  int /*<<< orphan*/  t5_tp_pio_array ;
typedef  int /*<<< orphan*/  t5_tp_mib_index_array ;
typedef  int /*<<< orphan*/  t5_pm_rx_array ;
typedef  int /*<<< orphan*/  t5_pcie_pdbg_array ;
struct sge_qbase_reg_field {int dummy; } ;
struct ireg_buf {int dummy; } ;
struct cudbg_vpd_data {int dummy; } ;
struct cudbg_ver_hdr {int dummy; } ;
struct cudbg_ulptx_la {int dummy; } ;
struct cudbg_ulprx_la {int dummy; } ;
struct cudbg_tp_la {int dummy; } ;
struct cudbg_tid_info_region_rev1 {int dummy; } ;
struct cudbg_tid_data {int dummy; } ;
struct cudbg_tcam {int max_tid; int /*<<< orphan*/  member_0; } ;
struct cudbg_rss_vf_conf {int dummy; } ;
struct cudbg_pm_stats {int dummy; } ;
struct cudbg_pbt_tables {int dummy; } ;
struct cudbg_mps_tcam {int dummy; } ;
struct cudbg_meminfo {int dummy; } ;
struct cudbg_mbox_log {int dummy; } ;
struct cudbg_hw_sched {int dummy; } ;
struct cudbg_clk_info {int dummy; } ;
struct cudbg_cim_qcfg {int dummy; } ;
struct cudbg_cim_pif_la {int dummy; } ;
struct TYPE_8__ {int vfcount; int mps_tcam_size; } ;
struct TYPE_6__ {int size; } ;
struct TYPE_7__ {int cim_la_size; int /*<<< orphan*/  chip; TYPE_4__ arch; TYPE_2__ devlog; } ;
struct adapter {TYPE_3__ params; TYPE_1__* mbox_log; } ;
struct TYPE_5__ {int size; } ;

/* Variables and functions */
 int const CHELSIO_CHIP_VERSION (int /*<<< orphan*/ ) ; 
#define  CHELSIO_T4 182 
#define  CHELSIO_T5 181 
#define  CHELSIO_T6 180 
 int CIM_IBQ_SIZE ; 
 int CIM_MALA_SIZE ; 
 int CIM_PIFLA_SIZE ; 
#define  CUDBG_CCTRL 179 
#define  CUDBG_CIM_IBQ_NCSI 178 
#define  CUDBG_CIM_IBQ_SGE0 177 
#define  CUDBG_CIM_IBQ_SGE1 176 
#define  CUDBG_CIM_IBQ_TP0 175 
#define  CUDBG_CIM_IBQ_TP1 174 
#define  CUDBG_CIM_IBQ_ULP 173 
#define  CUDBG_CIM_LA 172 
#define  CUDBG_CIM_MA_LA 171 
#define  CUDBG_CIM_OBQ_NCSI 170 
#define  CUDBG_CIM_OBQ_RXQ0 169 
#define  CUDBG_CIM_OBQ_RXQ1 168 
#define  CUDBG_CIM_OBQ_SGE 167 
#define  CUDBG_CIM_OBQ_ULP0 166 
#define  CUDBG_CIM_OBQ_ULP1 165 
#define  CUDBG_CIM_OBQ_ULP2 164 
#define  CUDBG_CIM_OBQ_ULP3 163 
#define  CUDBG_CIM_PIF_LA 162 
#define  CUDBG_CIM_QCFG 161 
#define  CUDBG_CLK 160 
#define  CUDBG_DEV_LOG 159 
#define  CUDBG_DUMP_CONTEXT 158 
#define  CUDBG_EDC0 157 
#define  CUDBG_EDC1 156 
#define  CUDBG_HMA 155 
#define  CUDBG_HMA_INDIRECT 154 
#define  CUDBG_HW_SCHED 153 
#define  CUDBG_LE_TCAM 152 
#define  CUDBG_MA_INDIRECT 151 
#define  CUDBG_MBOX_LOG 150 
#define  CUDBG_MC0 149 
#define  CUDBG_MC1 148 
#define  CUDBG_MEMINFO 147 
#define  CUDBG_MPS_TCAM 146 
 int CUDBG_NUM_PCIE_CONFIG_REGS ; 
#define  CUDBG_PATH_MTU 145 
#define  CUDBG_PBT_TABLE 144 
#define  CUDBG_PCIE_CONFIG 143 
#define  CUDBG_PCIE_INDIRECT 142 
#define  CUDBG_PM_INDIRECT 141 
#define  CUDBG_PM_STATS 140 
#define  CUDBG_QDESC 139 
#define  CUDBG_REG_DUMP 138 
#define  CUDBG_RSS 137 
#define  CUDBG_RSS_VF_CONF 136 
#define  CUDBG_SGE_INDIRECT 135 
#define  CUDBG_TID_INFO 134 
#define  CUDBG_TP_INDIRECT 133 
#define  CUDBG_TP_LA 132 
#define  CUDBG_ULPRX_LA 131 
#define  CUDBG_ULPTX_LA 130 
#define  CUDBG_UP_CIM_INDIRECT 129 
#define  CUDBG_VPD_DATA 128 
 int EDRAM0_ENABLE_F ; 
 int EDRAM0_SIZE_G (int) ; 
 int EDRAM1_ENABLE_F ; 
 int EDRAM1_SIZE_G (int) ; 
 int EXT_MEM0_ENABLE_F ; 
 int EXT_MEM0_SIZE_G (int) ; 
 int EXT_MEM1_ENABLE_F ; 
 int EXT_MEM1_SIZE_G (int) ; 
 int HMA_MUX_F ; 
 int IREG_NUM_ELEM ; 
 int /*<<< orphan*/  MA_EDRAM0_BAR_A ; 
 int /*<<< orphan*/  MA_EDRAM1_BAR_A ; 
 int /*<<< orphan*/  MA_EXT_MEMORY0_BAR_A ; 
 int /*<<< orphan*/  MA_EXT_MEMORY1_BAR_A ; 
 int /*<<< orphan*/  MA_TARGET_MEM_ENABLE_A ; 
 int NCCTRL_WIN ; 
 int NMTUS ; 
 int T4_REGMAP_SIZE ; 
 int T5_REGMAP_SIZE ; 
 int TPLA_SIZE ; 
 int cudbg_cim_obq_size (struct adapter*,int) ; 
 int cudbg_dump_context_size (struct adapter*) ; 
 int /*<<< orphan*/  cudbg_fill_le_tcam_info (struct adapter*,struct cudbg_tcam*) ; 
 int /*<<< orphan*/  cudbg_fill_qdesc_num_and_size (struct adapter*,int /*<<< orphan*/ *,int*) ; 
 int cudbg_mbytes_to_bytes (int) ; 
 int /*<<< orphan*/  is_t5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_t6 (int /*<<< orphan*/ ) ; 
 int t4_chip_rss_size (struct adapter*) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 cxgb4_get_entity_length(struct adapter *adap, u32 entity)
{
	struct cudbg_tcam tcam_region = { 0 };
	u32 value, n = 0, len = 0;

	switch (entity) {
	case CUDBG_REG_DUMP:
		switch (CHELSIO_CHIP_VERSION(adap->params.chip)) {
		case CHELSIO_T4:
			len = T4_REGMAP_SIZE;
			break;
		case CHELSIO_T5:
		case CHELSIO_T6:
			len = T5_REGMAP_SIZE;
			break;
		default:
			break;
		}
		break;
	case CUDBG_DEV_LOG:
		len = adap->params.devlog.size;
		break;
	case CUDBG_CIM_LA:
		if (is_t6(adap->params.chip)) {
			len = adap->params.cim_la_size / 10 + 1;
			len *= 10 * sizeof(u32);
		} else {
			len = adap->params.cim_la_size / 8;
			len *= 8 * sizeof(u32);
		}
		len += sizeof(u32); /* for reading CIM LA configuration */
		break;
	case CUDBG_CIM_MA_LA:
		len = 2 * CIM_MALA_SIZE * 5 * sizeof(u32);
		break;
	case CUDBG_CIM_QCFG:
		len = sizeof(struct cudbg_cim_qcfg);
		break;
	case CUDBG_CIM_IBQ_TP0:
	case CUDBG_CIM_IBQ_TP1:
	case CUDBG_CIM_IBQ_ULP:
	case CUDBG_CIM_IBQ_SGE0:
	case CUDBG_CIM_IBQ_SGE1:
	case CUDBG_CIM_IBQ_NCSI:
		len = CIM_IBQ_SIZE * 4 * sizeof(u32);
		break;
	case CUDBG_CIM_OBQ_ULP0:
		len = cudbg_cim_obq_size(adap, 0);
		break;
	case CUDBG_CIM_OBQ_ULP1:
		len = cudbg_cim_obq_size(adap, 1);
		break;
	case CUDBG_CIM_OBQ_ULP2:
		len = cudbg_cim_obq_size(adap, 2);
		break;
	case CUDBG_CIM_OBQ_ULP3:
		len = cudbg_cim_obq_size(adap, 3);
		break;
	case CUDBG_CIM_OBQ_SGE:
		len = cudbg_cim_obq_size(adap, 4);
		break;
	case CUDBG_CIM_OBQ_NCSI:
		len = cudbg_cim_obq_size(adap, 5);
		break;
	case CUDBG_CIM_OBQ_RXQ0:
		len = cudbg_cim_obq_size(adap, 6);
		break;
	case CUDBG_CIM_OBQ_RXQ1:
		len = cudbg_cim_obq_size(adap, 7);
		break;
	case CUDBG_EDC0:
		value = t4_read_reg(adap, MA_TARGET_MEM_ENABLE_A);
		if (value & EDRAM0_ENABLE_F) {
			value = t4_read_reg(adap, MA_EDRAM0_BAR_A);
			len = EDRAM0_SIZE_G(value);
		}
		len = cudbg_mbytes_to_bytes(len);
		break;
	case CUDBG_EDC1:
		value = t4_read_reg(adap, MA_TARGET_MEM_ENABLE_A);
		if (value & EDRAM1_ENABLE_F) {
			value = t4_read_reg(adap, MA_EDRAM1_BAR_A);
			len = EDRAM1_SIZE_G(value);
		}
		len = cudbg_mbytes_to_bytes(len);
		break;
	case CUDBG_MC0:
		value = t4_read_reg(adap, MA_TARGET_MEM_ENABLE_A);
		if (value & EXT_MEM0_ENABLE_F) {
			value = t4_read_reg(adap, MA_EXT_MEMORY0_BAR_A);
			len = EXT_MEM0_SIZE_G(value);
		}
		len = cudbg_mbytes_to_bytes(len);
		break;
	case CUDBG_MC1:
		value = t4_read_reg(adap, MA_TARGET_MEM_ENABLE_A);
		if (value & EXT_MEM1_ENABLE_F) {
			value = t4_read_reg(adap, MA_EXT_MEMORY1_BAR_A);
			len = EXT_MEM1_SIZE_G(value);
		}
		len = cudbg_mbytes_to_bytes(len);
		break;
	case CUDBG_RSS:
		len = t4_chip_rss_size(adap) * sizeof(u16);
		break;
	case CUDBG_RSS_VF_CONF:
		len = adap->params.arch.vfcount *
		      sizeof(struct cudbg_rss_vf_conf);
		break;
	case CUDBG_PATH_MTU:
		len = NMTUS * sizeof(u16);
		break;
	case CUDBG_PM_STATS:
		len = sizeof(struct cudbg_pm_stats);
		break;
	case CUDBG_HW_SCHED:
		len = sizeof(struct cudbg_hw_sched);
		break;
	case CUDBG_TP_INDIRECT:
		switch (CHELSIO_CHIP_VERSION(adap->params.chip)) {
		case CHELSIO_T5:
			n = sizeof(t5_tp_pio_array) +
			    sizeof(t5_tp_tm_pio_array) +
			    sizeof(t5_tp_mib_index_array);
			break;
		case CHELSIO_T6:
			n = sizeof(t6_tp_pio_array) +
			    sizeof(t6_tp_tm_pio_array) +
			    sizeof(t6_tp_mib_index_array);
			break;
		default:
			break;
		}
		n = n / (IREG_NUM_ELEM * sizeof(u32));
		len = sizeof(struct ireg_buf) * n;
		break;
	case CUDBG_SGE_INDIRECT:
		len = sizeof(struct ireg_buf) * 2 +
		      sizeof(struct sge_qbase_reg_field);
		break;
	case CUDBG_ULPRX_LA:
		len = sizeof(struct cudbg_ulprx_la);
		break;
	case CUDBG_TP_LA:
		len = sizeof(struct cudbg_tp_la) + TPLA_SIZE * sizeof(u64);
		break;
	case CUDBG_MEMINFO:
		len = sizeof(struct cudbg_ver_hdr) +
		      sizeof(struct cudbg_meminfo);
		break;
	case CUDBG_CIM_PIF_LA:
		len = sizeof(struct cudbg_cim_pif_la);
		len += 2 * CIM_PIFLA_SIZE * 6 * sizeof(u32);
		break;
	case CUDBG_CLK:
		len = sizeof(struct cudbg_clk_info);
		break;
	case CUDBG_PCIE_INDIRECT:
		n = sizeof(t5_pcie_pdbg_array) / (IREG_NUM_ELEM * sizeof(u32));
		len = sizeof(struct ireg_buf) * n * 2;
		break;
	case CUDBG_PM_INDIRECT:
		n = sizeof(t5_pm_rx_array) / (IREG_NUM_ELEM * sizeof(u32));
		len = sizeof(struct ireg_buf) * n * 2;
		break;
	case CUDBG_TID_INFO:
		len = sizeof(struct cudbg_tid_info_region_rev1);
		break;
	case CUDBG_PCIE_CONFIG:
		len = sizeof(u32) * CUDBG_NUM_PCIE_CONFIG_REGS;
		break;
	case CUDBG_DUMP_CONTEXT:
		len = cudbg_dump_context_size(adap);
		break;
	case CUDBG_MPS_TCAM:
		len = sizeof(struct cudbg_mps_tcam) *
		      adap->params.arch.mps_tcam_size;
		break;
	case CUDBG_VPD_DATA:
		len = sizeof(struct cudbg_vpd_data);
		break;
	case CUDBG_LE_TCAM:
		cudbg_fill_le_tcam_info(adap, &tcam_region);
		len = sizeof(struct cudbg_tcam) +
		      sizeof(struct cudbg_tid_data) * tcam_region.max_tid;
		break;
	case CUDBG_CCTRL:
		len = sizeof(u16) * NMTUS * NCCTRL_WIN;
		break;
	case CUDBG_MA_INDIRECT:
		if (CHELSIO_CHIP_VERSION(adap->params.chip) > CHELSIO_T5) {
			n = sizeof(t6_ma_ireg_array) /
			    (IREG_NUM_ELEM * sizeof(u32));
			len = sizeof(struct ireg_buf) * n * 2;
		}
		break;
	case CUDBG_ULPTX_LA:
		len = sizeof(struct cudbg_ver_hdr) +
		      sizeof(struct cudbg_ulptx_la);
		break;
	case CUDBG_UP_CIM_INDIRECT:
		n = 0;
		if (is_t5(adap->params.chip))
			n = sizeof(t5_up_cim_reg_array) /
			    ((IREG_NUM_ELEM + 1) * sizeof(u32));
		else if (is_t6(adap->params.chip))
			n = sizeof(t6_up_cim_reg_array) /
			    ((IREG_NUM_ELEM + 1) * sizeof(u32));
		len = sizeof(struct ireg_buf) * n;
		break;
	case CUDBG_PBT_TABLE:
		len = sizeof(struct cudbg_pbt_tables);
		break;
	case CUDBG_MBOX_LOG:
		len = sizeof(struct cudbg_mbox_log) * adap->mbox_log->size;
		break;
	case CUDBG_HMA_INDIRECT:
		if (CHELSIO_CHIP_VERSION(adap->params.chip) > CHELSIO_T5) {
			n = sizeof(t6_hma_ireg_array) /
			    (IREG_NUM_ELEM * sizeof(u32));
			len = sizeof(struct ireg_buf) * n;
		}
		break;
	case CUDBG_HMA:
		value = t4_read_reg(adap, MA_TARGET_MEM_ENABLE_A);
		if (value & HMA_MUX_F) {
			/* In T6, there's no MC1.  So, HMA shares MC1
			 * address space.
			 */
			value = t4_read_reg(adap, MA_EXT_MEMORY1_BAR_A);
			len = EXT_MEM1_SIZE_G(value);
		}
		len = cudbg_mbytes_to_bytes(len);
		break;
	case CUDBG_QDESC:
		cudbg_fill_qdesc_num_and_size(adap, NULL, &len);
		break;
	default:
		break;
	}

	return len;
}