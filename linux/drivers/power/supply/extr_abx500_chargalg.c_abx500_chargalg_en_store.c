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
struct TYPE_2__ {int ac_suspended; int usb_suspended; int suspended_change; } ;
struct abx500_chargalg {int /*<<< orphan*/  dev; int /*<<< orphan*/  chargalg_work; int /*<<< orphan*/  chargalg_wq; TYPE_1__ susp_status; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 

__attribute__((used)) static ssize_t abx500_chargalg_en_store(struct abx500_chargalg *di,
	const char *buf, size_t length)
{
	long int param;
	int ac_usb;
	int ret;

	ret = kstrtol(buf, 10, &param);
	if (ret < 0)
		return ret;

	ac_usb = param;
	switch (ac_usb) {
	case 0:
		/* Disable charging */
		di->susp_status.ac_suspended = true;
		di->susp_status.usb_suspended = true;
		di->susp_status.suspended_change = true;
		/* Trigger a state change */
		queue_work(di->chargalg_wq,
			&di->chargalg_work);
		break;
	case 1:
		/* Enable AC Charging */
		di->susp_status.ac_suspended = false;
		di->susp_status.suspended_change = true;
		/* Trigger a state change */
		queue_work(di->chargalg_wq,
			&di->chargalg_work);
		break;
	case 2:
		/* Enable USB charging */
		di->susp_status.usb_suspended = false;
		di->susp_status.suspended_change = true;
		/* Trigger a state change */
		queue_work(di->chargalg_wq,
			&di->chargalg_work);
		break;
	default:
		dev_info(di->dev, "Wrong input\n"
			"Enter 0. Disable AC/USB Charging\n"
			"1. Enable AC charging\n"
			"2. Enable USB Charging\n");
	};
	return strlen(buf);
}