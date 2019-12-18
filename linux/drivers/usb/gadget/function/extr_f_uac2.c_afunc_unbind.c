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
struct usb_function {int dummy; } ;
struct usb_configuration {int dummy; } ;
struct g_audio {int /*<<< orphan*/ * gadget; } ;

/* Variables and functions */
 struct g_audio* func_to_g_audio (struct usb_function*) ; 
 int /*<<< orphan*/  g_audio_cleanup (struct g_audio*) ; 
 int /*<<< orphan*/  usb_free_all_descriptors (struct usb_function*) ; 

__attribute__((used)) static void afunc_unbind(struct usb_configuration *c, struct usb_function *f)
{
	struct g_audio *agdev = func_to_g_audio(f);

	g_audio_cleanup(agdev);
	usb_free_all_descriptors(f);

	agdev->gadget = NULL;
}