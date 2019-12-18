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
struct typec_altmode {scalar_t__ svid; } ;

/* Variables and functions */
 scalar_t__ USB_TYPEC_NVIDIA_VLINK_SID ; 
 int /*<<< orphan*/  dp_altmode_remove (struct typec_altmode*) ; 

__attribute__((used)) static void nvidia_altmode_remove(struct typec_altmode *alt)
{
	if (alt->svid == USB_TYPEC_NVIDIA_VLINK_SID)
		dp_altmode_remove(alt);
}