#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  rate; } ;
struct cached_dev {int writeback_metadata; int writeback_running; int writeback_percent; int writeback_delay; int writeback_rate_minimum; int writeback_rate_p_term_inverse; int writeback_rate_i_term_inverse; int /*<<< orphan*/  writeback_rate_update; TYPE_2__ disk; int /*<<< orphan*/  writeback_rate_update_seconds; TYPE_1__ writeback_rate; int /*<<< orphan*/  writeback_keys; int /*<<< orphan*/  writeback_lock; int /*<<< orphan*/  in_flight; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCACHE_DEV_WB_RUNNING ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITEBACK_RATE_UPDATE_SECS_DEFAULT ; 
 int /*<<< orphan*/  atomic_long_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bch_keybuf_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_writeback_rate ; 

void bch_cached_dev_writeback_init(struct cached_dev *dc)
{
	sema_init(&dc->in_flight, 64);
	init_rwsem(&dc->writeback_lock);
	bch_keybuf_init(&dc->writeback_keys);

	dc->writeback_metadata		= true;
	dc->writeback_running		= false;
	dc->writeback_percent		= 10;
	dc->writeback_delay		= 30;
	atomic_long_set(&dc->writeback_rate.rate, 1024);
	dc->writeback_rate_minimum	= 8;

	dc->writeback_rate_update_seconds = WRITEBACK_RATE_UPDATE_SECS_DEFAULT;
	dc->writeback_rate_p_term_inverse = 40;
	dc->writeback_rate_i_term_inverse = 10000;

	WARN_ON(test_and_clear_bit(BCACHE_DEV_WB_RUNNING, &dc->disk.flags));
	INIT_DELAYED_WORK(&dc->writeback_rate_update, update_writeback_rate);
}