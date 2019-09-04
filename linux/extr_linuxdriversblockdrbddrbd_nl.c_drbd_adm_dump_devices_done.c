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
struct netlink_callback {int dummy; } ;

/* Variables and functions */
 int put_resource_in_arg0 (struct netlink_callback*,int) ; 

int drbd_adm_dump_devices_done(struct netlink_callback *cb) {
	return put_resource_in_arg0(cb, 7);
}