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
typedef  int u8 ;
struct cec_pin {int la_mask; } ;
struct cec_adapter {struct cec_pin* pin; } ;

/* Variables and functions */
 int CEC_LOG_ADDR_INVALID ; 

__attribute__((used)) static int cec_pin_adap_log_addr(struct cec_adapter *adap, u8 log_addr)
{
	struct cec_pin *pin = adap->pin;

	if (log_addr == CEC_LOG_ADDR_INVALID)
		pin->la_mask = 0;
	else
		pin->la_mask |= (1 << log_addr);
	return 0;
}