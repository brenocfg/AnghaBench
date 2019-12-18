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
struct usb_interface_cache {int num_altsetting; struct usb_host_interface* altsetting; } ;
struct usb_host_interface {struct usb_interface_cache* string; struct usb_interface_cache* endpoint; } ;
struct kref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usb_interface_cache*) ; 
 struct usb_interface_cache* ref_to_usb_interface_cache (struct kref*) ; 

void usb_release_interface_cache(struct kref *ref)
{
	struct usb_interface_cache *intfc = ref_to_usb_interface_cache(ref);
	int j;

	for (j = 0; j < intfc->num_altsetting; j++) {
		struct usb_host_interface *alt = &intfc->altsetting[j];

		kfree(alt->endpoint);
		kfree(alt->string);
	}
	kfree(intfc);
}