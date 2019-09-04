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
struct isku_device {int /*<<< orphan*/  actual_profile; } ;

/* Variables and functions */

__attribute__((used)) static void isku_profile_activated(struct isku_device *isku, uint new_profile)
{
	isku->actual_profile = new_profile;
}