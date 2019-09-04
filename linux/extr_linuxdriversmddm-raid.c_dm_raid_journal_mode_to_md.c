#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mode; int /*<<< orphan*/  param; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* _raid456_journal_mode ; 
 int /*<<< orphan*/  strcasecmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dm_raid_journal_mode_to_md(const char *mode)
{
	int m = ARRAY_SIZE(_raid456_journal_mode);

	while (m--)
		if (!strcasecmp(mode, _raid456_journal_mode[m].param))
			return _raid456_journal_mode[m].mode;

	return -EINVAL;
}