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
typedef  int uint ;
struct kone_device {int actual_profile; TYPE_1__* profiles; int /*<<< orphan*/  actual_dpi; } ;
struct TYPE_2__ {int /*<<< orphan*/  startup_dpi; } ;

/* Variables and functions */

__attribute__((used)) static void kone_profile_activated(struct kone_device *kone, uint new_profile)
{
	kone->actual_profile = new_profile;
	kone->actual_dpi = kone->profiles[new_profile - 1].startup_dpi;
}