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
typedef  int u32 ;
struct octeon_device {int pcie_port; scalar_t__ chip; } ;
struct octeon_cn6xxx {int /*<<< orphan*/  conf; } ;

/* Variables and functions */
 scalar_t__ CFG_GET_IS_SLI_BP_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ CFG_GET_OQ_INTR_PKT (int /*<<< orphan*/ ) ; 
 scalar_t__ CFG_GET_OQ_INTR_TIME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CN6XXX_SLI_OQ_INT_LEVEL_PKTS ; 
 int /*<<< orphan*/  CN6XXX_SLI_OQ_INT_LEVEL_TIME ; 
 int /*<<< orphan*/  CN6XXX_SLI_OQ_WMARK ; 
 int /*<<< orphan*/  CN6XXX_SLI_PKT_DATA_OUT_ES64 ; 
 int /*<<< orphan*/  CN6XXX_SLI_PKT_DATA_OUT_NS ; 
 int /*<<< orphan*/  CN6XXX_SLI_PKT_DATA_OUT_ROR ; 
 int /*<<< orphan*/  CN6XXX_SLI_PKT_DPADDR ; 
 int /*<<< orphan*/  CN6XXX_SLI_PKT_OUT_BMODE ; 
 int /*<<< orphan*/  CN6XXX_SLI_PKT_PCIE_PORT64 ; 
 int /*<<< orphan*/  CN6XXX_SLI_PKT_SLIST_ES64 ; 
 int /*<<< orphan*/  CN6XXX_SLI_PKT_SLIST_NS ; 
 int /*<<< orphan*/  CN6XXX_SLI_PKT_SLIST_ROR ; 
 int lio_cn6xxx_get_oq_ticks (struct octeon_device*,int) ; 
 int /*<<< orphan*/  octeon_write_csr (struct octeon_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  octeon_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 

void lio_cn6xxx_setup_global_output_regs(struct octeon_device *oct)
{
	u32 time_threshold;
	struct octeon_cn6xxx *cn6xxx = (struct octeon_cn6xxx *)oct->chip;

	/* / Select PCI-E Port for all Output queues */
	octeon_write_csr64(oct, CN6XXX_SLI_PKT_PCIE_PORT64,
			   (oct->pcie_port * 0x5555555555555555ULL));

	if (CFG_GET_IS_SLI_BP_ON(cn6xxx->conf)) {
		octeon_write_csr64(oct, CN6XXX_SLI_OQ_WMARK, 32);
	} else {
		/* / Set Output queue watermark to 0 to disable backpressure */
		octeon_write_csr64(oct, CN6XXX_SLI_OQ_WMARK, 0);
	}

	/* / Select Packet count instead of bytes for SLI_PKTi_CNTS[CNT] */
	octeon_write_csr(oct, CN6XXX_SLI_PKT_OUT_BMODE, 0);

	/* Select ES, RO, NS setting from register for Output Queue Packet
	 * Address
	 */
	octeon_write_csr(oct, CN6XXX_SLI_PKT_DPADDR, 0xFFFFFFFF);

	/* No Relaxed Ordering, No Snoop, 64-bit swap for Output
	 * Queue ScatterList
	 */
	octeon_write_csr(oct, CN6XXX_SLI_PKT_SLIST_ROR, 0);
	octeon_write_csr(oct, CN6XXX_SLI_PKT_SLIST_NS, 0);

	/* / ENDIAN_SPECIFIC CHANGES - 0 works for LE. */
#ifdef __BIG_ENDIAN_BITFIELD
	octeon_write_csr64(oct, CN6XXX_SLI_PKT_SLIST_ES64,
			   0x5555555555555555ULL);
#else
	octeon_write_csr64(oct, CN6XXX_SLI_PKT_SLIST_ES64, 0ULL);
#endif

	/* / No Relaxed Ordering, No Snoop, 64-bit swap for Output Queue Data */
	octeon_write_csr(oct, CN6XXX_SLI_PKT_DATA_OUT_ROR, 0);
	octeon_write_csr(oct, CN6XXX_SLI_PKT_DATA_OUT_NS, 0);
	octeon_write_csr64(oct, CN6XXX_SLI_PKT_DATA_OUT_ES64,
			   0x5555555555555555ULL);

	/* / Set up interrupt packet and time threshold */
	octeon_write_csr(oct, CN6XXX_SLI_OQ_INT_LEVEL_PKTS,
			 (u32)CFG_GET_OQ_INTR_PKT(cn6xxx->conf));
	time_threshold =
		lio_cn6xxx_get_oq_ticks(oct, (u32)
					CFG_GET_OQ_INTR_TIME(cn6xxx->conf));

	octeon_write_csr(oct, CN6XXX_SLI_OQ_INT_LEVEL_TIME, time_threshold);
}