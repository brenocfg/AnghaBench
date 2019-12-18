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
struct brcms_info {int /*<<< orphan*/  wlc; TYPE_1__* pub; } ;
struct TYPE_2__ {scalar_t__ up; } ;

/* Variables and functions */
 int brcms_c_up (int /*<<< orphan*/ ) ; 

int brcms_up(struct brcms_info *wl)
{
	int error = 0;

	if (wl->pub->up)
		return 0;

	error = brcms_c_up(wl->wlc);

	return error;
}