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
 int ENOTSUPP ; 
 scalar_t__ USB_TYPEC_NVIDIA_VLINK_SID ; 
 int dp_altmode_probe (struct typec_altmode*) ; 

__attribute__((used)) static int nvidia_altmode_probe(struct typec_altmode *alt)
{
	if (alt->svid == USB_TYPEC_NVIDIA_VLINK_SID)
		return dp_altmode_probe(alt);
	else
		return -ENOTSUPP;
}