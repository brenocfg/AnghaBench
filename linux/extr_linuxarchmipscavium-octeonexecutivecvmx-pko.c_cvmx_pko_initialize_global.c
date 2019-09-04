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
struct TYPE_2__ {int size; int /*<<< orphan*/  pool; } ;
union cvmx_pko_reg_cmd_buf {int u64; TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_FPA_OUTPUT_BUFFER_POOL ; 
 int CVMX_FPA_OUTPUT_BUFFER_POOL_SIZE ; 
 int /*<<< orphan*/  CVMX_PKO_REG_CMD_BUF ; 
 int /*<<< orphan*/  CVMX_PKO_REG_QUEUE_MODE ; 
 int /*<<< orphan*/  OCTEON_CN38XX ; 
 int /*<<< orphan*/  OCTEON_CN52XX ; 
 int /*<<< orphan*/  OCTEON_CN56XX ; 
 int /*<<< orphan*/  OCTEON_CN58XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_pko_chip_init () ; 
 int cvmx_helper_get_last_ipd_port (int) ; 
 int cvmx_helper_get_number_of_interfaces () ; 
 int cvmx_pko_get_base_queue (int) ; 
 int cvmx_pko_get_num_queues (int) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 

void cvmx_pko_initialize_global(void)
{
	union cvmx_pko_reg_cmd_buf config;

	/*
	 * Set the size of the PKO command buffers to an odd number of
	 * 64bit words. This allows the normal two word send to stay
	 * aligned and never span a command word buffer.
	 */
	config.u64 = 0;
	config.s.pool = CVMX_FPA_OUTPUT_BUFFER_POOL;
	config.s.size = CVMX_FPA_OUTPUT_BUFFER_POOL_SIZE / 8 - 1;

	cvmx_write_csr(CVMX_PKO_REG_CMD_BUF, config.u64);

	/*
	 * Chip-specific setup.
	 */
	__cvmx_pko_chip_init();

	/*
	 * If we aren't using all of the queues optimize PKO's
	 * internal memory.
	 */
	if (OCTEON_IS_MODEL(OCTEON_CN38XX) || OCTEON_IS_MODEL(OCTEON_CN58XX)
	    || OCTEON_IS_MODEL(OCTEON_CN56XX)
	    || OCTEON_IS_MODEL(OCTEON_CN52XX)) {
		int num_interfaces = cvmx_helper_get_number_of_interfaces();
		int last_port =
		    cvmx_helper_get_last_ipd_port(num_interfaces - 1);
		int max_queues =
		    cvmx_pko_get_base_queue(last_port) +
		    cvmx_pko_get_num_queues(last_port);
		if (OCTEON_IS_MODEL(OCTEON_CN38XX)) {
			if (max_queues <= 32)
				cvmx_write_csr(CVMX_PKO_REG_QUEUE_MODE, 2);
			else if (max_queues <= 64)
				cvmx_write_csr(CVMX_PKO_REG_QUEUE_MODE, 1);
		} else {
			if (max_queues <= 64)
				cvmx_write_csr(CVMX_PKO_REG_QUEUE_MODE, 2);
			else if (max_queues <= 128)
				cvmx_write_csr(CVMX_PKO_REG_QUEUE_MODE, 1);
		}
	}
}