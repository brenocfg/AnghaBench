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
struct rtsx_hw_param {int ocp_glitch; int /*<<< orphan*/  interrupt_en; } ;
struct rtsx_cr_option {int dev_flags; int ltr_en; int ocp_en; int /*<<< orphan*/  sd_800mA_ocp_thd; int /*<<< orphan*/  sd_400mA_ocp_thd; int /*<<< orphan*/  ltr_l1off_snooze_sspwrgate; int /*<<< orphan*/  ltr_l1off_sspwrgate; int /*<<< orphan*/  l1_snooze_delay; int /*<<< orphan*/  dev_aspm_mode; int /*<<< orphan*/  ltr_l1off_latency; int /*<<< orphan*/  ltr_idle_latency; int /*<<< orphan*/  ltr_active_latency; } ;
struct rtsx_pcr {int extra_caps; int num_slots; int /*<<< orphan*/ * ops; int /*<<< orphan*/  reg_pm_ctrl3; int /*<<< orphan*/  ms_pull_ctl_disable_tbl; int /*<<< orphan*/  ms_pull_ctl_enable_tbl; int /*<<< orphan*/  sd_pull_ctl_disable_tbl; int /*<<< orphan*/  sd_pull_ctl_enable_tbl; int /*<<< orphan*/  ic_version; void* rx_initial_phase; void* tx_initial_phase; int /*<<< orphan*/  aspm_en; void* sd30_drive_sel_3v3; void* sd30_drive_sel_1v8; int /*<<< orphan*/  card_drive_sel; scalar_t__ flags; struct rtsx_hw_param hw_param; struct rtsx_cr_option option; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPM_L1_EN ; 
 void* CFG_DRIVER_TYPE_B ; 
 int /*<<< orphan*/  DEV_ASPM_DYNAMIC ; 
 int EXTRA_CAPS_SD_SDR104 ; 
 int EXTRA_CAPS_SD_SDR50 ; 
 int /*<<< orphan*/  L1_SNOOZE_DELAY_DEF ; 
 int /*<<< orphan*/  LTR_ACTIVE_LATENCY_DEF ; 
 int /*<<< orphan*/  LTR_IDLE_LATENCY_DEF ; 
 int /*<<< orphan*/  LTR_L1OFF_LATENCY_DEF ; 
 int /*<<< orphan*/  LTR_L1OFF_SNOOZE_SSPWRGATE_5250_DEF ; 
 int /*<<< orphan*/  LTR_L1OFF_SSPWRGATE_5250_DEF ; 
 int LTR_L1SS_PWR_GATE_CHECK_CARD_EN ; 
 int LTR_L1SS_PWR_GATE_EN ; 
 int /*<<< orphan*/  RTS524A_PM_CTRL3 ; 
 int /*<<< orphan*/  RTS5260_DVCC_OCP_THD_550 ; 
 int /*<<< orphan*/  RTS5260_DVCC_OCP_THD_970 ; 
 int /*<<< orphan*/  RTSX_CARD_DRIVE_DEFAULT ; 
 int SDVIO_OCP_GLITCH_800U ; 
 int SD_OCP_GLITCH_100U ; 
 int /*<<< orphan*/  SD_OC_INT_EN ; 
 void* SET_CLOCK_PHASE (int,int,int) ; 
 int /*<<< orphan*/  rts5260_get_ic_version (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rts5260_ms_pull_ctl_disable_tbl ; 
 int /*<<< orphan*/  rts5260_ms_pull_ctl_enable_tbl ; 
 int /*<<< orphan*/  rts5260_pcr_ops ; 
 int /*<<< orphan*/  rts5260_sd_pull_ctl_disable_tbl ; 
 int /*<<< orphan*/  rts5260_sd_pull_ctl_enable_tbl ; 

void rts5260_init_params(struct rtsx_pcr *pcr)
{
	struct rtsx_cr_option *option = &pcr->option;
	struct rtsx_hw_param *hw_param = &pcr->hw_param;

	pcr->extra_caps = EXTRA_CAPS_SD_SDR50 | EXTRA_CAPS_SD_SDR104;
	pcr->num_slots = 2;

	pcr->flags = 0;
	pcr->card_drive_sel = RTSX_CARD_DRIVE_DEFAULT;
	pcr->sd30_drive_sel_1v8 = CFG_DRIVER_TYPE_B;
	pcr->sd30_drive_sel_3v3 = CFG_DRIVER_TYPE_B;
	pcr->aspm_en = ASPM_L1_EN;
	pcr->tx_initial_phase = SET_CLOCK_PHASE(1, 29, 16);
	pcr->rx_initial_phase = SET_CLOCK_PHASE(24, 6, 5);

	pcr->ic_version = rts5260_get_ic_version(pcr);
	pcr->sd_pull_ctl_enable_tbl = rts5260_sd_pull_ctl_enable_tbl;
	pcr->sd_pull_ctl_disable_tbl = rts5260_sd_pull_ctl_disable_tbl;
	pcr->ms_pull_ctl_enable_tbl = rts5260_ms_pull_ctl_enable_tbl;
	pcr->ms_pull_ctl_disable_tbl = rts5260_ms_pull_ctl_disable_tbl;

	pcr->reg_pm_ctrl3 = RTS524A_PM_CTRL3;

	pcr->ops = &rts5260_pcr_ops;

	option->dev_flags = (LTR_L1SS_PWR_GATE_CHECK_CARD_EN
				| LTR_L1SS_PWR_GATE_EN);
	option->ltr_en = true;

	/* init latency of active, idle, L1OFF to 60us, 300us, 3ms */
	option->ltr_active_latency = LTR_ACTIVE_LATENCY_DEF;
	option->ltr_idle_latency = LTR_IDLE_LATENCY_DEF;
	option->ltr_l1off_latency = LTR_L1OFF_LATENCY_DEF;
	option->dev_aspm_mode = DEV_ASPM_DYNAMIC;
	option->l1_snooze_delay = L1_SNOOZE_DELAY_DEF;
	option->ltr_l1off_sspwrgate = LTR_L1OFF_SSPWRGATE_5250_DEF;
	option->ltr_l1off_snooze_sspwrgate =
		LTR_L1OFF_SNOOZE_SSPWRGATE_5250_DEF;

	option->ocp_en = 1;
	if (option->ocp_en)
		hw_param->interrupt_en |= SD_OC_INT_EN;
	hw_param->ocp_glitch =  SD_OCP_GLITCH_100U | SDVIO_OCP_GLITCH_800U;
	option->sd_400mA_ocp_thd = RTS5260_DVCC_OCP_THD_550;
	option->sd_800mA_ocp_thd = RTS5260_DVCC_OCP_THD_970;
}