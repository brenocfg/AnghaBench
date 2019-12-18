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
struct ptp_clock_info {int dummy; } ;
typedef  enum ptp_pin_function { ____Placeholder_ptp_pin_function } ptp_pin_function ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  PTP_PF_EXTTS 131 
#define  PTP_PF_NONE 130 
#define  PTP_PF_PEROUT 129 
#define  PTP_PF_PHYSYNC 128 

__attribute__((used)) static int mv88e6352_ptp_verify(struct ptp_clock_info *ptp, unsigned int pin,
				enum ptp_pin_function func, unsigned int chan)
{
	switch (func) {
	case PTP_PF_NONE:
	case PTP_PF_EXTTS:
		break;
	case PTP_PF_PEROUT:
	case PTP_PF_PHYSYNC:
		return -EOPNOTSUPP;
	}
	return 0;
}