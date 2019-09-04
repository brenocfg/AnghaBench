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
struct TYPE_2__ {scalar_t__ cfg_rtry; } ;
union cvmx_pemx_ctl_status {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PEMX_CTL_STATUS (int) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 disable_cfg_read_retry(void)
{
	u32 retry_cnt;

	union cvmx_pemx_ctl_status pemx_ctl;
	pemx_ctl.u64 = cvmx_read_csr(CVMX_PEMX_CTL_STATUS(1));
	retry_cnt =  pemx_ctl.s.cfg_rtry;
	pemx_ctl.s.cfg_rtry = 0;
	cvmx_write_csr(CVMX_PEMX_CTL_STATUS(1), pemx_ctl.u64);
	return retry_cnt;
}