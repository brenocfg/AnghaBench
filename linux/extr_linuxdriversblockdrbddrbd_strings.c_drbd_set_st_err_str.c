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
typedef  enum drbd_state_rv { ____Placeholder_drbd_state_rv } drbd_state_rv ;

/* Variables and functions */
 int SS_AFTER_LAST_ERROR ; 
 int SS_TWO_PRIMARIES ; 
 char const** drbd_state_sw_errors ; 

const char *drbd_set_st_err_str(enum drbd_state_rv err)
{
	return err <= SS_AFTER_LAST_ERROR ? "TOO_SMALL" :
	       err > SS_TWO_PRIMARIES ? "TOO_LARGE"
			: drbd_state_sw_errors[-err];
}