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
struct ptp_pin_desc {int func; unsigned int chan; } ;
struct ptp_clock_info {unsigned int n_pins; unsigned int n_ext_ts; unsigned int n_per_out; scalar_t__ (* verify ) (struct ptp_clock_info*,unsigned int,int,unsigned int) ;struct ptp_pin_desc* pin_config; } ;
struct ptp_clock {struct ptp_clock_info* info; } ;
typedef  enum ptp_pin_function { ____Placeholder_ptp_pin_function } ptp_pin_function ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  PTP_PF_EXTTS 131 
#define  PTP_PF_NONE 130 
#define  PTP_PF_PEROUT 129 
#define  PTP_PF_PHYSYNC 128 
 int /*<<< orphan*/  pr_err (char*,int,unsigned int) ; 
 int /*<<< orphan*/  ptp_disable_pinfunc (struct ptp_clock_info*,int,unsigned int) ; 
 scalar_t__ stub1 (struct ptp_clock_info*,unsigned int,int,unsigned int) ; 

int ptp_set_pinfunc(struct ptp_clock *ptp, unsigned int pin,
		    enum ptp_pin_function func, unsigned int chan)
{
	struct ptp_clock_info *info = ptp->info;
	struct ptp_pin_desc *pin1 = NULL, *pin2 = &info->pin_config[pin];
	unsigned int i;

	/* Check to see if any other pin previously had this function. */
	for (i = 0; i < info->n_pins; i++) {
		if (info->pin_config[i].func == func &&
		    info->pin_config[i].chan == chan) {
			pin1 = &info->pin_config[i];
			break;
		}
	}
	if (pin1 && i == pin)
		return 0;

	/* Check the desired function and channel. */
	switch (func) {
	case PTP_PF_NONE:
		break;
	case PTP_PF_EXTTS:
		if (chan >= info->n_ext_ts)
			return -EINVAL;
		break;
	case PTP_PF_PEROUT:
		if (chan >= info->n_per_out)
			return -EINVAL;
		break;
	case PTP_PF_PHYSYNC:
		if (chan != 0)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	if (info->verify(info, pin, func, chan)) {
		pr_err("driver cannot use function %u on pin %u\n", func, chan);
		return -EOPNOTSUPP;
	}

	/* Disable whatever function was previously assigned. */
	if (pin1) {
		ptp_disable_pinfunc(info, func, chan);
		pin1->func = PTP_PF_NONE;
		pin1->chan = 0;
	}
	ptp_disable_pinfunc(info, pin2->func, pin2->chan);
	pin2->func = func;
	pin2->chan = chan;

	return 0;
}