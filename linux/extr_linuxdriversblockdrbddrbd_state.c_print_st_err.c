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
typedef  union drbd_state {int dummy; } drbd_state ;
struct drbd_device {int dummy; } ;
typedef  enum drbd_state_rv { ____Placeholder_drbd_state_rv } drbd_state_rv ;

/* Variables and functions */
 int SS_IN_TRANSIENT_STATE ; 
 int /*<<< orphan*/  drbd_err (struct drbd_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_set_st_err_str (int) ; 
 int /*<<< orphan*/  print_st (struct drbd_device*,char*,union drbd_state) ; 

void print_st_err(struct drbd_device *device, union drbd_state os,
	          union drbd_state ns, enum drbd_state_rv err)
{
	if (err == SS_IN_TRANSIENT_STATE)
		return;
	drbd_err(device, "State change failed: %s\n", drbd_set_st_err_str(err));
	print_st(device, " state", os);
	print_st(device, "wanted", ns);
}