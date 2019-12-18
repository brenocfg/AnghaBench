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
struct TYPE_2__ {int pkt_lend; int wqe_lend; } ;
union cvmx_ipd_ctl_status {int /*<<< orphan*/  u64; TYPE_1__ s; } ;

/* Variables and functions */
 scalar_t__ CVMX_FPA_OUTPUT_BUFFER_POOL ; 
 int /*<<< orphan*/  CVMX_FPA_OUTPUT_BUFFER_POOL_SIZE ; 
 scalar_t__ CVMX_FPA_PACKET_POOL ; 
 int /*<<< orphan*/  CVMX_FPA_PACKET_POOL_SIZE ; 
 scalar_t__ CVMX_FPA_WQE_POOL ; 
 int /*<<< orphan*/  CVMX_FPA_WQE_POOL_SIZE ; 
 int /*<<< orphan*/  CVMX_IPD_CTL_STATUS ; 
 int /*<<< orphan*/  cvm_oct_mem_fill_fpa (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cvmx_fpa_enable () ; 
 int /*<<< orphan*/  cvmx_helper_setup_red (int,int) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int num_packet_buffers ; 

__attribute__((used)) static void cvm_oct_configure_common_hw(void)
{
	/* Setup the FPA */
	cvmx_fpa_enable();
	cvm_oct_mem_fill_fpa(CVMX_FPA_PACKET_POOL, CVMX_FPA_PACKET_POOL_SIZE,
			     num_packet_buffers);
	cvm_oct_mem_fill_fpa(CVMX_FPA_WQE_POOL, CVMX_FPA_WQE_POOL_SIZE,
			     num_packet_buffers);
	if (CVMX_FPA_OUTPUT_BUFFER_POOL != CVMX_FPA_PACKET_POOL)
		cvm_oct_mem_fill_fpa(CVMX_FPA_OUTPUT_BUFFER_POOL,
				     CVMX_FPA_OUTPUT_BUFFER_POOL_SIZE, 1024);

#ifdef __LITTLE_ENDIAN
	{
		union cvmx_ipd_ctl_status ipd_ctl_status;

		ipd_ctl_status.u64 = cvmx_read_csr(CVMX_IPD_CTL_STATUS);
		ipd_ctl_status.s.pkt_lend = 1;
		ipd_ctl_status.s.wqe_lend = 1;
		cvmx_write_csr(CVMX_IPD_CTL_STATUS, ipd_ctl_status.u64);
	}
#endif

	cvmx_helper_setup_red(num_packet_buffers / 4, num_packet_buffers / 8);
}