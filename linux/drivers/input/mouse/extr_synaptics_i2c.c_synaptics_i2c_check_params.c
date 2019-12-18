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
struct synaptics_i2c {scalar_t__ scan_rate_param; scalar_t__ no_decel_param; scalar_t__ no_filter_param; scalar_t__ reduce_report_param; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 scalar_t__ no_decel ; 
 scalar_t__ no_filter ; 
 scalar_t__ reduce_report ; 
 scalar_t__ scan_rate ; 
 int /*<<< orphan*/  set_scan_rate (struct synaptics_i2c*,scalar_t__) ; 
 int /*<<< orphan*/  synaptics_i2c_reset_config (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void synaptics_i2c_check_params(struct synaptics_i2c *touch)
{
	bool reset = false;

	if (scan_rate != touch->scan_rate_param)
		set_scan_rate(touch, scan_rate);

	if (no_decel != touch->no_decel_param) {
		touch->no_decel_param = no_decel;
		reset = true;
	}

	if (no_filter != touch->no_filter_param) {
		touch->no_filter_param = no_filter;
		reset = true;
	}

	if (reduce_report != touch->reduce_report_param) {
		touch->reduce_report_param = reduce_report;
		reset = true;
	}

	if (reset)
		synaptics_i2c_reset_config(touch->client);
}