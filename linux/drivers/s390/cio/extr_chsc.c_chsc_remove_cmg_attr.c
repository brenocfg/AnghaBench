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
struct channel_subsystem {int /*<<< orphan*/ * chps; } ;

/* Variables and functions */
 int __MAX_CHPID ; 
 int /*<<< orphan*/  chp_remove_cmg_attr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chsc_remove_cmg_attr(struct channel_subsystem *css)
{
	int i;

	for (i = 0; i <= __MAX_CHPID; i++) {
		if (!css->chps[i])
			continue;
		chp_remove_cmg_attr(css->chps[i]);
	}
}