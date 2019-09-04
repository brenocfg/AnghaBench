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
struct log_c {int /*<<< orphan*/  clean_bits; int /*<<< orphan*/  flush_failed; } ;
struct dm_dirty_log {scalar_t__ context; } ;
typedef  int /*<<< orphan*/  region_t ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  log_set_bit (struct log_c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void core_clear_region(struct dm_dirty_log *log, region_t region)
{
	struct log_c *lc = (struct log_c *) log->context;
	if (likely(!lc->flush_failed))
		log_set_bit(lc, lc->clean_bits, region);
}