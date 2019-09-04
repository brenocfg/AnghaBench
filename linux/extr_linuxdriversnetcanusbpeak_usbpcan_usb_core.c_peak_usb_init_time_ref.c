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
struct peak_usb_adapter {int dummy; } ;
struct peak_time_ref {struct peak_usb_adapter const* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct peak_time_ref*,int /*<<< orphan*/ ,int) ; 

void peak_usb_init_time_ref(struct peak_time_ref *time_ref,
			    const struct peak_usb_adapter *adapter)
{
	if (time_ref) {
		memset(time_ref, 0, sizeof(struct peak_time_ref));
		time_ref->adapter = adapter;
	}
}