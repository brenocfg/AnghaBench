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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,char const*) ; 

__attribute__((used)) static void fail_mutex_acquire_message(struct hfi1_devdata *dd,
				       const char *func)
{
	dd_dev_err(dd,
		   "%s: hardware mutex stuck - suggest rebooting the machine\n",
		   func);
}