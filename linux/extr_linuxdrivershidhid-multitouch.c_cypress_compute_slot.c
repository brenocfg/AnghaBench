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
struct mt_usages {scalar_t__* contactid; } ;
struct mt_application {scalar_t__ num_received; } ;

/* Variables and functions */

__attribute__((used)) static int cypress_compute_slot(struct mt_application *application,
				struct mt_usages *slot)
{
	if (*slot->contactid != 0 || application->num_received == 0)
		return *slot->contactid;
	else
		return -1;
}