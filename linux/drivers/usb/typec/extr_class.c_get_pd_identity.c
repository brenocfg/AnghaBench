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
struct usb_pd_identity {int dummy; } ;
struct typec_partner {struct usb_pd_identity* identity; } ;
struct typec_cable {struct usb_pd_identity* identity; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_typec_cable (struct device*) ; 
 scalar_t__ is_typec_partner (struct device*) ; 
 struct typec_cable* to_typec_cable (struct device*) ; 
 struct typec_partner* to_typec_partner (struct device*) ; 

__attribute__((used)) static struct usb_pd_identity *get_pd_identity(struct device *dev)
{
	if (is_typec_partner(dev)) {
		struct typec_partner *partner = to_typec_partner(dev);

		return partner->identity;
	} else if (is_typec_cable(dev)) {
		struct typec_cable *cable = to_typec_cable(dev);

		return cable->identity;
	}
	return NULL;
}