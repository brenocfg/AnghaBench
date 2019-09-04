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
struct TYPE_2__ {scalar_t__ crs_dr; } ;
union cvmx_pemx_int_sum {TYPE_1__ s; int /*<<< orphan*/  u64; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PEMX_INT_SUM (int) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_cfg_retry(void)
{
	union cvmx_pemx_int_sum pemx_int_sum;
	pemx_int_sum.u64 = cvmx_read_csr(CVMX_PEMX_INT_SUM(1));
	if (pemx_int_sum.s.crs_dr)
		return 1;
	return 0;
}