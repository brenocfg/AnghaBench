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
struct cec_pin {int monitor_all; } ;
struct cec_adapter {struct cec_pin* pin; } ;

/* Variables and functions */

__attribute__((used)) static int cec_pin_adap_monitor_all_enable(struct cec_adapter *adap,
						  bool enable)
{
	struct cec_pin *pin = adap->pin;

	pin->monitor_all = enable;
	return 0;
}