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
union drbd_state {int i; } ;

/* Variables and functions */

__attribute__((used)) static union drbd_state
apply_mask_val(union drbd_state os, union drbd_state mask, union drbd_state val)
{
	union drbd_state ns;
	ns.i = (os.i & ~mask.i) | val.i;
	return ns;
}