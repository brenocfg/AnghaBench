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
struct rx_drvinfo_819x_usb {int RxRate; scalar_t__ RxHT; } ;

/* Variables and functions */
#define  DESC90_RATE11M 131 
#define  DESC90_RATE1M 130 
#define  DESC90_RATE2M 129 
#define  DESC90_RATE5_5M 128 

__attribute__((used)) static inline bool rx_hal_is_cck_rate(struct rx_drvinfo_819x_usb *pdrvinfo)
{
	if (pdrvinfo->RxHT)
		return false;

	switch (pdrvinfo->RxRate) {
	case DESC90_RATE1M:
	case DESC90_RATE2M:
	case DESC90_RATE5_5M:
	case DESC90_RATE11M:
		return true;
	default:
		return false;
	}
}