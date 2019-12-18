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
struct mapped_device {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMF_SUSPENDED_INTERNALLY ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int dm_suspended_internally_md(struct mapped_device *md)
{
	return test_bit(DMF_SUSPENDED_INTERNALLY, &md->flags);
}