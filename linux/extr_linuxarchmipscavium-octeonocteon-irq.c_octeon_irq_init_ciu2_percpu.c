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

/* Variables and functions */
 int CVMX_CIU2_EN_PPX_IP2_WRKQ (int) ; 
 int /*<<< orphan*/  CVMX_CIU2_SUM_PPX_IP2 (int) ; 
 int cvmx_get_core_num () ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void octeon_irq_init_ciu2_percpu(void)
{
	u64 regx, ipx;
	int coreid = cvmx_get_core_num();
	u64 base = CVMX_CIU2_EN_PPX_IP2_WRKQ(coreid);

	/*
	 * Disable All CIU2 Interrupts. The ones we need will be
	 * enabled later.  Read the SUM register so we know the write
	 * completed.
	 *
	 * There are 9 registers and 3 IPX levels with strides 0x1000
	 * and 0x200 respectivly.  Use loops to clear them.
	 */
	for (regx = 0; regx <= 0x8000; regx += 0x1000) {
		for (ipx = 0; ipx <= 0x400; ipx += 0x200)
			cvmx_write_csr(base + regx + ipx, 0);
	}

	cvmx_read_csr(CVMX_CIU2_SUM_PPX_IP2(coreid));
}