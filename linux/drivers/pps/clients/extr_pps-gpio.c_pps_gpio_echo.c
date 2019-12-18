#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ expires; } ;
struct pps_gpio_device_data {TYPE_4__ echo_timer; scalar_t__ echo_timeout; TYPE_2__* pps; int /*<<< orphan*/  echo_pin; } ;
struct TYPE_7__ {int mode; } ;
struct pps_device {TYPE_3__ params; } ;
struct TYPE_5__ {int mode; } ;
struct TYPE_6__ {TYPE_1__ params; } ;

/* Variables and functions */
#define  PPS_CAPTUREASSERT 129 
#define  PPS_CAPTURECLEAR 128 
 int PPS_ECHOASSERT ; 
 int PPS_ECHOCLEAR ; 
 int /*<<< orphan*/  add_timer (TYPE_4__*) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static void pps_gpio_echo(struct pps_device *pps, int event, void *data)
{
	/* add_timer() needs to write into info->echo_timer */
	struct pps_gpio_device_data *info = data;

	switch (event) {
	case PPS_CAPTUREASSERT:
		if (pps->params.mode & PPS_ECHOASSERT)
			gpiod_set_value(info->echo_pin, 1);
		break;

	case PPS_CAPTURECLEAR:
		if (pps->params.mode & PPS_ECHOCLEAR)
			gpiod_set_value(info->echo_pin, 1);
		break;
	}

	/* fire the timer */
	if (info->pps->params.mode & (PPS_ECHOASSERT | PPS_ECHOCLEAR)) {
		info->echo_timer.expires = jiffies + info->echo_timeout;
		add_timer(&info->echo_timer);
	}
}