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
struct mapped_device {int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_put (struct mapped_device*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wq_has_sleeper (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rq_completed(struct mapped_device *md)
{
	/* nudge anyone waiting on suspend queue */
	if (unlikely(wq_has_sleeper(&md->wait)))
		wake_up(&md->wait);

	/*
	 * dm_put() must be at the end of this function. See the comment above
	 */
	dm_put(md);
}