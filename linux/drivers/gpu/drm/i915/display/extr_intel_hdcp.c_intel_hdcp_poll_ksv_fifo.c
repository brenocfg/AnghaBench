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
struct intel_hdcp_shim {int (* read_ksv_ready ) (struct intel_digital_port*,int*) ;} ;
struct intel_digital_port {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int __wait_for (int,int,int,int,int) ; 
 int stub1 (struct intel_digital_port*,int*) ; 

__attribute__((used)) static int intel_hdcp_poll_ksv_fifo(struct intel_digital_port *intel_dig_port,
				    const struct intel_hdcp_shim *shim)
{
	int ret, read_ret;
	bool ksv_ready;

	/* Poll for ksv list ready (spec says max time allowed is 5s) */
	ret = __wait_for(read_ret = shim->read_ksv_ready(intel_dig_port,
							 &ksv_ready),
			 read_ret || ksv_ready, 5 * 1000 * 1000, 1000,
			 100 * 1000);
	if (ret)
		return ret;
	if (read_ret)
		return read_ret;
	if (!ksv_ready)
		return -ETIMEDOUT;

	return 0;
}