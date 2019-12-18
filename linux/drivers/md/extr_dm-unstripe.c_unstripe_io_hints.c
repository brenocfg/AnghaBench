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
struct unstripe_c {int /*<<< orphan*/  chunk_size; } ;
struct queue_limits {int /*<<< orphan*/  chunk_sectors; } ;
struct dm_target {struct unstripe_c* private; } ;

/* Variables and functions */

__attribute__((used)) static void unstripe_io_hints(struct dm_target *ti,
			       struct queue_limits *limits)
{
	struct unstripe_c *uc = ti->private;

	limits->chunk_sectors = uc->chunk_size;
}