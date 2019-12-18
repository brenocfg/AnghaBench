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
struct team {int /*<<< orphan*/ * mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  __team_no_mode ; 

__attribute__((used)) static bool team_is_mode_set(struct team *team)
{
	return team->mode != &__team_no_mode;
}