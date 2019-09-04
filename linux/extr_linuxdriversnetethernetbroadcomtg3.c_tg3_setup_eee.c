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
typedef  int u32 ;
struct TYPE_2__ {int tx_lpi_timer; scalar_t__ eee_enabled; scalar_t__ tx_lpi_enabled; } ;
struct tg3 {TYPE_1__ eee; } ;

/* Variables and functions */
 scalar_t__ ASIC_REV_5717 ; 
 scalar_t__ CHIPREV_ID_57765_A0 ; 
 int /*<<< orphan*/  ENABLE_APE ; 
 int TG3_CPMU_DBTMR1_PCIEXIT_2047US ; 
 int TG3_CPMU_DBTMR2_APE_TX_2047US ; 
 int TG3_CPMU_DBTMR2_TXIDXEQ_2047US ; 
 int TG3_CPMU_EEEMD_APE_TX_DET_EN ; 
 int TG3_CPMU_EEEMD_EEE_ENABLE ; 
 int TG3_CPMU_EEEMD_ERLY_L1_XIT_DET ; 
 int TG3_CPMU_EEEMD_LPI_IN_RX ; 
 int TG3_CPMU_EEEMD_LPI_IN_TX ; 
 int TG3_CPMU_EEEMD_SND_IDX_DET_EN ; 
 int /*<<< orphan*/  TG3_CPMU_EEE_CTRL ; 
 int TG3_CPMU_EEE_CTRL_EXIT_20_1_US ; 
 int /*<<< orphan*/  TG3_CPMU_EEE_DBTMR1 ; 
 int /*<<< orphan*/  TG3_CPMU_EEE_DBTMR2 ; 
 int TG3_CPMU_EEE_LNKIDL_APE_TX_MT ; 
 int /*<<< orphan*/  TG3_CPMU_EEE_LNKIDL_CTRL ; 
 int TG3_CPMU_EEE_LNKIDL_PCIE_NL0 ; 
 int TG3_CPMU_EEE_LNKIDL_UART_IDL ; 
 int /*<<< orphan*/  TG3_CPMU_EEE_MODE ; 
 scalar_t__ tg3_asic_rev (struct tg3*) ; 
 scalar_t__ tg3_chip_rev_id (struct tg3*) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32_f (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tg3_setup_eee(struct tg3 *tp)
{
	u32 val;

	val = TG3_CPMU_EEE_LNKIDL_PCIE_NL0 |
	      TG3_CPMU_EEE_LNKIDL_UART_IDL;
	if (tg3_chip_rev_id(tp) == CHIPREV_ID_57765_A0)
		val |= TG3_CPMU_EEE_LNKIDL_APE_TX_MT;

	tw32_f(TG3_CPMU_EEE_LNKIDL_CTRL, val);

	tw32_f(TG3_CPMU_EEE_CTRL,
	       TG3_CPMU_EEE_CTRL_EXIT_20_1_US);

	val = TG3_CPMU_EEEMD_ERLY_L1_XIT_DET |
	      (tp->eee.tx_lpi_enabled ? TG3_CPMU_EEEMD_LPI_IN_TX : 0) |
	      TG3_CPMU_EEEMD_LPI_IN_RX |
	      TG3_CPMU_EEEMD_EEE_ENABLE;

	if (tg3_asic_rev(tp) != ASIC_REV_5717)
		val |= TG3_CPMU_EEEMD_SND_IDX_DET_EN;

	if (tg3_flag(tp, ENABLE_APE))
		val |= TG3_CPMU_EEEMD_APE_TX_DET_EN;

	tw32_f(TG3_CPMU_EEE_MODE, tp->eee.eee_enabled ? val : 0);

	tw32_f(TG3_CPMU_EEE_DBTMR1,
	       TG3_CPMU_DBTMR1_PCIEXIT_2047US |
	       (tp->eee.tx_lpi_timer & 0xffff));

	tw32_f(TG3_CPMU_EEE_DBTMR2,
	       TG3_CPMU_DBTMR2_APE_TX_2047US |
	       TG3_CPMU_DBTMR2_TXIDXEQ_2047US);
}