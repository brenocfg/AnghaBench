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
typedef  enum ath10k_bus { ____Placeholder_ath10k_bus } ath10k_bus ;

/* Variables and functions */
#define  ATH10K_BUS_AHB 132 
#define  ATH10K_BUS_PCI 131 
#define  ATH10K_BUS_SDIO 130 
#define  ATH10K_BUS_SNOC 129 
#define  ATH10K_BUS_USB 128 

__attribute__((used)) static inline const char *ath10k_bus_str(enum ath10k_bus bus)
{
	switch (bus) {
	case ATH10K_BUS_PCI:
		return "pci";
	case ATH10K_BUS_AHB:
		return "ahb";
	case ATH10K_BUS_SDIO:
		return "sdio";
	case ATH10K_BUS_USB:
		return "usb";
	case ATH10K_BUS_SNOC:
		return "snoc";
	}

	return "unknown";
}