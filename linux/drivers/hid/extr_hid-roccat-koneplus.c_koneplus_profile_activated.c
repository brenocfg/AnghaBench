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
typedef  int /*<<< orphan*/  uint ;
struct koneplus_device {int /*<<< orphan*/  actual_profile; } ;

/* Variables and functions */

__attribute__((used)) static void koneplus_profile_activated(struct koneplus_device *koneplus,
		uint new_profile)
{
	koneplus->actual_profile = new_profile;
}