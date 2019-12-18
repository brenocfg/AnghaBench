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
struct octeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN6XXX_SLI_WINDOW_CTL ; 
 int /*<<< orphan*/  PCIE_MPS_DEFAULT ; 
 int /*<<< orphan*/  PCIE_MRRS_256B ; 
 int /*<<< orphan*/  lio_cn68xx_setup_pkt_ctl_regs (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_cn6xxx_enable_error_reporting (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_cn6xxx_setup_global_input_regs (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_cn6xxx_setup_global_output_regs (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_cn6xxx_setup_pcie_mps (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_cn6xxx_setup_pcie_mrrs (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lio_cn68xx_setup_device_regs(struct octeon_device *oct)
{
	lio_cn6xxx_setup_pcie_mps(oct, PCIE_MPS_DEFAULT);
	lio_cn6xxx_setup_pcie_mrrs(oct, PCIE_MRRS_256B);
	lio_cn6xxx_enable_error_reporting(oct);

	lio_cn6xxx_setup_global_input_regs(oct);
	lio_cn68xx_setup_pkt_ctl_regs(oct);
	lio_cn6xxx_setup_global_output_regs(oct);

	/* Default error timeout value should be 0x200000 to avoid host hang
	 * when reads invalid register
	 */
	octeon_write_csr64(oct, CN6XXX_SLI_WINDOW_CTL, 0x200000ULL);

	return 0;
}