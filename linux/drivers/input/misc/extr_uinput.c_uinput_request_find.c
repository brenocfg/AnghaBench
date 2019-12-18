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
struct uinput_request {int dummy; } ;
struct uinput_device {struct uinput_request** requests; } ;

/* Variables and functions */
 unsigned int UINPUT_NUM_REQUESTS ; 

__attribute__((used)) static struct uinput_request *uinput_request_find(struct uinput_device *udev,
						  unsigned int id)
{
	/* Find an input request, by ID. Returns NULL if the ID isn't valid. */
	if (id >= UINPUT_NUM_REQUESTS)
		return NULL;

	return udev->requests[id];
}