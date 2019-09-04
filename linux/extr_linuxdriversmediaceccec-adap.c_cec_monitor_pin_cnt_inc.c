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
struct cec_adapter {scalar_t__ monitor_pin_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  adap_monitor_pin_enable ; 
 int call_op (struct cec_adapter*,int /*<<< orphan*/ ,int) ; 

int cec_monitor_pin_cnt_inc(struct cec_adapter *adap)
{
	int ret = 0;

	if (adap->monitor_pin_cnt == 0)
		ret = call_op(adap, adap_monitor_pin_enable, 1);
	if (ret == 0)
		adap->monitor_pin_cnt++;
	return ret;
}