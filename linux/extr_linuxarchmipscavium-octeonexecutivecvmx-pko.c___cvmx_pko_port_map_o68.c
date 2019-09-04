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
struct TYPE_2__ {int eid; int ipid; int qos_mask; int crc; int min_pkt; int intr; int pipe; } ;
union cvmx_pko_mem_iport_ptrs {scalar_t__ u64; TYPE_1__ s; } ;
typedef  scalar_t__ cvmx_helper_interface_mode_t ;

/* Variables and functions */
 scalar_t__ CVMX_HELPER_INTERFACE_MODE_DISABLED ; 
 scalar_t__ CVMX_HELPER_INTERFACE_MODE_LOOP ; 
 int /*<<< orphan*/  CVMX_PKO_MEM_IPORT_PTRS ; 
 int __cvmx_pko_int (int,int) ; 
 int cvmx_helper_get_interface_index_num (int) ; 
 int cvmx_helper_get_interface_num (int) ; 
 scalar_t__ cvmx_helper_interface_get_mode (int) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void __cvmx_pko_port_map_o68(void)
{
	int port;
	int interface, index;
	cvmx_helper_interface_mode_t mode;
	union cvmx_pko_mem_iport_ptrs config;

	/*
	 * Initialize every iport with the invalid eid.
	 */
	config.u64 = 0;
	config.s.eid = 31; /* Invalid */
	for (port = 0; port < 128; port++) {
		config.s.ipid = port;
		cvmx_write_csr(CVMX_PKO_MEM_IPORT_PTRS, config.u64);
	}

	/*
	 * Set up PKO_MEM_IPORT_PTRS
	 */
	for (port = 0; port < 48; port++) {
		interface = cvmx_helper_get_interface_num(port);
		index = cvmx_helper_get_interface_index_num(port);
		mode = cvmx_helper_interface_get_mode(interface);
		if (mode == CVMX_HELPER_INTERFACE_MODE_DISABLED)
			continue;

		config.s.ipid = port;
		config.s.qos_mask = 0xff;
		config.s.crc = 1;
		config.s.min_pkt = 1;
		config.s.intr = __cvmx_pko_int(interface, index);
		config.s.eid = config.s.intr;
		config.s.pipe = (mode == CVMX_HELPER_INTERFACE_MODE_LOOP) ?
			index : port;
		cvmx_write_csr(CVMX_PKO_MEM_IPORT_PTRS, config.u64);
	}
}