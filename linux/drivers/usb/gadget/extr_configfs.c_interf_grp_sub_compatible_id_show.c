#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct config_item {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {scalar_t__ ext_compat_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,scalar_t__,int) ; 
 TYPE_1__* to_usb_os_desc (struct config_item*) ; 

__attribute__((used)) static ssize_t interf_grp_sub_compatible_id_show(struct config_item *item,
						 char *page)
{
	memcpy(page, to_usb_os_desc(item)->ext_compat_id + 8, 8);
	return 8;
}