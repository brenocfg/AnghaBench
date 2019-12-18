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
struct dm_buffer {scalar_t__ last_accessed; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int time_after_eq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool older_than(struct dm_buffer *b, unsigned long age_hz)
{
	return time_after_eq(jiffies, b->last_accessed + age_hz);
}