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
struct wusbhc {int ports_max; int /*<<< orphan*/ * port; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wusb_port_init (int /*<<< orphan*/ *) ; 

int wusbhc_rh_create(struct wusbhc *wusbhc)
{
	int result = -ENOMEM;
	size_t port_size, itr;
	port_size = wusbhc->ports_max * sizeof(wusbhc->port[0]);
	wusbhc->port = kzalloc(port_size, GFP_KERNEL);
	if (wusbhc->port == NULL)
		goto error_port_alloc;
	for (itr = 0; itr < wusbhc->ports_max; itr++)
		wusb_port_init(&wusbhc->port[itr]);
	result = 0;
error_port_alloc:
	return result;
}