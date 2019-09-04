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
struct adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSUM_HAS_PSEUDO_HDR_F ; 
 int /*<<< orphan*/  L1_CACHE_BYTES ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PKTSHIFT_M ; 
 int /*<<< orphan*/  PKTSHIFT_V (int) ; 
 int /*<<< orphan*/  SGE_CONTROL_A ; 
 int /*<<< orphan*/  TP_INGRESS_CONFIG_A ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int rx_dma_offset ; 
 int /*<<< orphan*/  t4_fixup_host_params (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_set_reg_field (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_tp_wr_bits_indirect (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adap_init0_tweaks(struct adapter *adapter)
{
	/*
	 * Fix up various Host-Dependent Parameters like Page Size, Cache
	 * Line Size, etc.  The firmware default is for a 4KB Page Size and
	 * 64B Cache Line Size ...
	 */
	t4_fixup_host_params(adapter, PAGE_SIZE, L1_CACHE_BYTES);

	/*
	 * Process module parameters which affect early initialization.
	 */
	if (rx_dma_offset != 2 && rx_dma_offset != 0) {
		dev_err(&adapter->pdev->dev,
			"Ignoring illegal rx_dma_offset=%d, using 2\n",
			rx_dma_offset);
		rx_dma_offset = 2;
	}
	t4_set_reg_field(adapter, SGE_CONTROL_A,
			 PKTSHIFT_V(PKTSHIFT_M),
			 PKTSHIFT_V(rx_dma_offset));

	/*
	 * Don't include the "IP Pseudo Header" in CPL_RX_PKT checksums: Linux
	 * adds the pseudo header itself.
	 */
	t4_tp_wr_bits_indirect(adapter, TP_INGRESS_CONFIG_A,
			       CSUM_HAS_PSEUDO_HDR_F, 0);

	return 0;
}