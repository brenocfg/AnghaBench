#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct cached_dev {int /*<<< orphan*/  writeback_rate; int /*<<< orphan*/  writeback_percent; TYPE_1__ disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCACHE_DEV_DETACHING ; 
 unsigned int bch_next_delay (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int writeback_delay(struct cached_dev *dc,
				    unsigned int sectors)
{
	if (test_bit(BCACHE_DEV_DETACHING, &dc->disk.flags) ||
	    !dc->writeback_percent)
		return 0;

	return bch_next_delay(&dc->writeback_rate, sectors);
}