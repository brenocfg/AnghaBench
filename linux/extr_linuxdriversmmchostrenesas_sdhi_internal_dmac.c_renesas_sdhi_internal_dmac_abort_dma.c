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
struct tmio_mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_CM_RST ; 
 int RST_DTRANRST0 ; 
 int RST_DTRANRST1 ; 
 int RST_RESERVED_BITS ; 
 int /*<<< orphan*/  SDHI_INTERNAL_DMAC_RX_IN_USE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  global_flags ; 
 int /*<<< orphan*/  renesas_sdhi_internal_dmac_dm_write (struct tmio_mmc_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  renesas_sdhi_internal_dmac_enable_dma (struct tmio_mmc_host*,int) ; 

__attribute__((used)) static void
renesas_sdhi_internal_dmac_abort_dma(struct tmio_mmc_host *host) {
	u64 val = RST_DTRANRST1 | RST_DTRANRST0;

	renesas_sdhi_internal_dmac_enable_dma(host, false);

	renesas_sdhi_internal_dmac_dm_write(host, DM_CM_RST,
					    RST_RESERVED_BITS & ~val);
	renesas_sdhi_internal_dmac_dm_write(host, DM_CM_RST,
					    RST_RESERVED_BITS | val);

	clear_bit(SDHI_INTERNAL_DMAC_RX_IN_USE, &global_flags);

	renesas_sdhi_internal_dmac_enable_dma(host, true);
}