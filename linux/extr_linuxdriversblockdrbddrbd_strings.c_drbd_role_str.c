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
typedef  enum drbd_role { ____Placeholder_drbd_role } drbd_role ;

/* Variables and functions */
 int R_SECONDARY ; 
 char const** drbd_role_s_names ; 

const char *drbd_role_str(enum drbd_role s)
{
	return s > R_SECONDARY   ? "TOO_LARGE" : drbd_role_s_names[s];
}