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
struct octeon_device {int /*<<< orphan*/  coproc_clock_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN6XXX_MIO_PTP_CLOCK_CFG ; 
 int /*<<< orphan*/  CN6XXX_MIO_PTP_CLOCK_COMP ; 
 scalar_t__ NSEC_PER_SEC ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 int lio_pci_readq (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_pci_writeq (struct octeon_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void liquidio_ptp_init(struct octeon_device *oct)
{
	u64 clock_comp, cfg;

	clock_comp = (u64)NSEC_PER_SEC << 32;
	do_div(clock_comp, oct->coproc_clock_rate);
	lio_pci_writeq(oct, clock_comp, CN6XXX_MIO_PTP_CLOCK_COMP);

	/* Enable */
	cfg = lio_pci_readq(oct, CN6XXX_MIO_PTP_CLOCK_CFG);
	lio_pci_writeq(oct, cfg | 0x01, CN6XXX_MIO_PTP_CLOCK_CFG);
}