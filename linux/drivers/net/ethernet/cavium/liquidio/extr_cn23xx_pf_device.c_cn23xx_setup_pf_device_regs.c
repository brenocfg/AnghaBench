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
 int /*<<< orphan*/  CN23XX_INPUT_JABBER ; 
 int /*<<< orphan*/  CN23XX_SLI_PKT_IN_JABBER ; 
 int /*<<< orphan*/  CN23XX_SLI_WINDOW_CTL ; 
 int /*<<< orphan*/  CN23XX_SLI_WINDOW_CTL_DEFAULT ; 
 int /*<<< orphan*/  cn23xx_enable_error_reporting (struct octeon_device*) ; 
 scalar_t__ cn23xx_pf_setup_global_input_regs (struct octeon_device*) ; 
 int /*<<< orphan*/  cn23xx_pf_setup_global_output_regs (struct octeon_device*) ; 
 int /*<<< orphan*/  cn23xx_setup_global_mac_regs (struct octeon_device*) ; 
 int /*<<< orphan*/  octeon_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cn23xx_setup_pf_device_regs(struct octeon_device *oct)
{
	cn23xx_enable_error_reporting(oct);

	/* program the MAC(0..3)_RINFO before setting up input/output regs */
	cn23xx_setup_global_mac_regs(oct);

	if (cn23xx_pf_setup_global_input_regs(oct))
		return -1;

	cn23xx_pf_setup_global_output_regs(oct);

	/* Default error timeout value should be 0x200000 to avoid host hang
	 * when reads invalid register
	 */
	octeon_write_csr64(oct, CN23XX_SLI_WINDOW_CTL,
			   CN23XX_SLI_WINDOW_CTL_DEFAULT);

	/* set SLI_PKT_IN_JABBER to handle large VXLAN packets */
	octeon_write_csr64(oct, CN23XX_SLI_PKT_IN_JABBER, CN23XX_INPUT_JABBER);
	return 0;
}