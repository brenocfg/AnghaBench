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
struct nokia_modem_device {scalar_t__ ssi_protocol; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ssip_reset_event (scalar_t__) ; 

__attribute__((used)) static void do_nokia_modem_rst_ind_tasklet(unsigned long data)
{
	struct nokia_modem_device *modem = (struct nokia_modem_device *)data;

	if (!modem)
		return;

	dev_info(modem->device, "CMT rst line change detected\n");

	if (modem->ssi_protocol)
		ssip_reset_event(modem->ssi_protocol);
}