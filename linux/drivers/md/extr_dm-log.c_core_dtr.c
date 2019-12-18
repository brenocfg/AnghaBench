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
struct log_c {int /*<<< orphan*/  clean_bits; } ;
struct dm_dirty_log {scalar_t__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_log_context (struct log_c*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void core_dtr(struct dm_dirty_log *log)
{
	struct log_c *lc = (struct log_c *) log->context;

	vfree(lc->clean_bits);
	destroy_log_context(lc);
}