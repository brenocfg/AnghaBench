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
struct pvc_device {scalar_t__ ether; scalar_t__ main; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_carrier_off (scalar_t__) ; 
 scalar_t__ netif_carrier_ok (scalar_t__) ; 
 int /*<<< orphan*/  netif_carrier_on (scalar_t__) ; 

__attribute__((used)) static inline void pvc_carrier(int on, struct pvc_device *pvc)
{
	if (on) {
		if (pvc->main)
			if (!netif_carrier_ok(pvc->main))
				netif_carrier_on(pvc->main);
		if (pvc->ether)
			if (!netif_carrier_ok(pvc->ether))
				netif_carrier_on(pvc->ether);
	} else {
		if (pvc->main)
			if (netif_carrier_ok(pvc->main))
				netif_carrier_off(pvc->main);
		if (pvc->ether)
			if (netif_carrier_ok(pvc->ether))
				netif_carrier_off(pvc->ether);
	}
}