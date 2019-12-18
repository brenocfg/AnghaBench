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
struct octeon_device {scalar_t__ chip_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN6XXX_SLI_PKT_INSTR_ENB ; 
 int /*<<< orphan*/  CN6XXX_SLI_PKT_OUT_ENB ; 
 scalar_t__ OCTEON_CN66XX ; 
 scalar_t__ OCTEON_CN68XX ; 
 int /*<<< orphan*/  octeon_write_csr (struct octeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void force_io_queues_off(struct octeon_device *oct)
{
	if ((oct->chip_id == OCTEON_CN66XX) ||
	    (oct->chip_id == OCTEON_CN68XX)) {
		/* Reset the Enable bits for Input Queues. */
		octeon_write_csr(oct, CN6XXX_SLI_PKT_INSTR_ENB, 0);

		/* Reset the Enable bits for Output Queues. */
		octeon_write_csr(oct, CN6XXX_SLI_PKT_OUT_ENB, 0);
	}
}