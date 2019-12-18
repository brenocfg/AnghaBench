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
struct octeon_device {scalar_t__ chip; } ;
struct octeon_cn6xxx {int /*<<< orphan*/  conf; } ;

/* Variables and functions */
 scalar_t__ CFG_GET_IS_SLI_BP_ON (int /*<<< orphan*/ ) ; 
 int CFG_GET_OQ_MAX_Q (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHIP_CONF (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CN68XX_SLI_TX_PIPE ; 
 int /*<<< orphan*/  CN6XXX_SLI_PKT_CTL ; 
 int /*<<< orphan*/  cn6xxx ; 
 int octeon_read_csr64 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lio_cn68xx_setup_pkt_ctl_regs(struct octeon_device *oct)
{
	struct octeon_cn6xxx *cn68xx = (struct octeon_cn6xxx *)oct->chip;
	u64 pktctl, tx_pipe, max_oqs;

	pktctl = octeon_read_csr64(oct, CN6XXX_SLI_PKT_CTL);

	/* 68XX specific */
	max_oqs = CFG_GET_OQ_MAX_Q(CHIP_CONF(oct, cn6xxx));
	tx_pipe  = octeon_read_csr64(oct, CN68XX_SLI_TX_PIPE);
	tx_pipe &= 0xffffffffff00ffffULL; /* clear out NUMP field */
	tx_pipe |= max_oqs << 16; /* put max_oqs in NUMP field */
	octeon_write_csr64(oct, CN68XX_SLI_TX_PIPE, tx_pipe);

	if (CFG_GET_IS_SLI_BP_ON(cn68xx->conf))
		pktctl |= 0xF;
	else
		/* Disable per-port backpressure. */
		pktctl &= ~0xF;
	octeon_write_csr64(oct, CN6XXX_SLI_PKT_CTL, pktctl);
}