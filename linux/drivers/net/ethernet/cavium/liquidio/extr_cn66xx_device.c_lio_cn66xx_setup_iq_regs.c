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
typedef  int /*<<< orphan*/  u32 ;
struct octeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN66XX_SLI_IQ_BP64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_cn6xxx_setup_iq_regs (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lio_cn66xx_setup_iq_regs(struct octeon_device *oct, u32 iq_no)
{
	lio_cn6xxx_setup_iq_regs(oct, iq_no);

	/* Backpressure for this queue - WMARK set to all F's. This effectively
	 * disables the backpressure mechanism.
	 */
	octeon_write_csr64(oct, CN66XX_SLI_IQ_BP64(iq_no),
			   (0xFFFFFFFFULL << 32));
}