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
struct spi_device {int dummy; } ;
struct fpga_manager {struct spi_device* priv; } ;
typedef  enum fpga_mgr_states { ____Placeholder_fpga_mgr_states } fpga_mgr_states ;

/* Variables and functions */
 int /*<<< orphan*/  BUSY ; 
 int /*<<< orphan*/  DONE ; 
 scalar_t__ ENOERR ; 
 int FPGA_MGR_STATE_OPERATING ; 
 int FPGA_MGR_STATE_UNKNOWN ; 
 scalar_t__ get_err (unsigned long*) ; 
 int /*<<< orphan*/  get_status (struct spi_device*,unsigned long*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static enum fpga_mgr_states machxo2_spi_state(struct fpga_manager *mgr)
{
	struct spi_device *spi = mgr->priv;
	unsigned long status;

	get_status(spi, &status);
	if (!test_bit(BUSY, &status) && test_bit(DONE, &status) &&
	    get_err(&status) == ENOERR)
		return FPGA_MGR_STATE_OPERATING;

	return FPGA_MGR_STATE_UNKNOWN;
}