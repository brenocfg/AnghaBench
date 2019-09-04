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
union drbd_dev_state {scalar_t__ conn; } ;
struct seq_file {int dummy; } ;
struct drbd_device {int rs_last_mark; unsigned long* rs_mark_time; unsigned long* rs_mark_left; unsigned long rs_start; unsigned long rs_paused; unsigned long c_sync_rate; unsigned long ov_left; unsigned long long ov_stop_sector; unsigned long bm_resync_fo; } ;

/* Variables and functions */
 int BM_BLOCK_SHIFT ; 
 unsigned long long BM_SECT_PER_BIT ; 
 unsigned long Bit2KB (unsigned long) ; 
 scalar_t__ C_SYNC_TARGET ; 
 scalar_t__ C_VERIFY_S ; 
 scalar_t__ C_VERIFY_T ; 
 int DRBD_SYNC_MARKS ; 
 unsigned long HZ ; 
 unsigned long long ULLONG_MAX ; 
 unsigned long drbd_bm_bits (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_get_syncer_progress (struct drbd_device*,union drbd_dev_state,unsigned long*,unsigned long*,unsigned int*) ; 
 int drbd_proc_details ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_printf_with_thousands_grouping (struct seq_file*,unsigned long) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 scalar_t__ verify_can_do_stop_sector (struct drbd_device*) ; 

__attribute__((used)) static void drbd_syncer_progress(struct drbd_device *device, struct seq_file *seq,
		union drbd_dev_state state)
{
	unsigned long db, dt, dbdt, rt, rs_total, rs_left;
	unsigned int res;
	int i, x, y;
	int stalled = 0;

	drbd_get_syncer_progress(device, state, &rs_total, &rs_left, &res);

	x = res/50;
	y = 20-x;
	seq_puts(seq, "\t[");
	for (i = 1; i < x; i++)
		seq_putc(seq, '=');
	seq_putc(seq, '>');
	for (i = 0; i < y; i++)
		seq_putc(seq, '.');
	seq_puts(seq, "] ");

	if (state.conn == C_VERIFY_S || state.conn == C_VERIFY_T)
		seq_puts(seq, "verified:");
	else
		seq_puts(seq, "sync'ed:");
	seq_printf(seq, "%3u.%u%% ", res / 10, res % 10);

	/* if more than a few GB, display in MB */
	if (rs_total > (4UL << (30 - BM_BLOCK_SHIFT)))
		seq_printf(seq, "(%lu/%lu)M",
			    (unsigned long) Bit2KB(rs_left >> 10),
			    (unsigned long) Bit2KB(rs_total >> 10));
	else
		seq_printf(seq, "(%lu/%lu)K",
			    (unsigned long) Bit2KB(rs_left),
			    (unsigned long) Bit2KB(rs_total));

	seq_puts(seq, "\n\t");

	/* see drivers/md/md.c
	 * We do not want to overflow, so the order of operands and
	 * the * 100 / 100 trick are important. We do a +1 to be
	 * safe against division by zero. We only estimate anyway.
	 *
	 * dt: time from mark until now
	 * db: blocks written from mark until now
	 * rt: remaining time
	 */
	/* Rolling marks. last_mark+1 may just now be modified.  last_mark+2 is
	 * at least (DRBD_SYNC_MARKS-2)*DRBD_SYNC_MARK_STEP old, and has at
	 * least DRBD_SYNC_MARK_STEP time before it will be modified. */
	/* ------------------------ ~18s average ------------------------ */
	i = (device->rs_last_mark + 2) % DRBD_SYNC_MARKS;
	dt = (jiffies - device->rs_mark_time[i]) / HZ;
	if (dt > 180)
		stalled = 1;

	if (!dt)
		dt++;
	db = device->rs_mark_left[i] - rs_left;
	rt = (dt * (rs_left / (db/100+1)))/100; /* seconds */

	seq_printf(seq, "finish: %lu:%02lu:%02lu",
		rt / 3600, (rt % 3600) / 60, rt % 60);

	dbdt = Bit2KB(db/dt);
	seq_puts(seq, " speed: ");
	seq_printf_with_thousands_grouping(seq, dbdt);
	seq_puts(seq, " (");
	/* ------------------------- ~3s average ------------------------ */
	if (drbd_proc_details >= 1) {
		/* this is what drbd_rs_should_slow_down() uses */
		i = (device->rs_last_mark + DRBD_SYNC_MARKS-1) % DRBD_SYNC_MARKS;
		dt = (jiffies - device->rs_mark_time[i]) / HZ;
		if (!dt)
			dt++;
		db = device->rs_mark_left[i] - rs_left;
		dbdt = Bit2KB(db/dt);
		seq_printf_with_thousands_grouping(seq, dbdt);
		seq_puts(seq, " -- ");
	}

	/* --------------------- long term average ---------------------- */
	/* mean speed since syncer started
	 * we do account for PausedSync periods */
	dt = (jiffies - device->rs_start - device->rs_paused) / HZ;
	if (dt == 0)
		dt = 1;
	db = rs_total - rs_left;
	dbdt = Bit2KB(db/dt);
	seq_printf_with_thousands_grouping(seq, dbdt);
	seq_putc(seq, ')');

	if (state.conn == C_SYNC_TARGET ||
	    state.conn == C_VERIFY_S) {
		seq_puts(seq, " want: ");
		seq_printf_with_thousands_grouping(seq, device->c_sync_rate);
	}
	seq_printf(seq, " K/sec%s\n", stalled ? " (stalled)" : "");

	if (drbd_proc_details >= 1) {
		/* 64 bit:
		 * we convert to sectors in the display below. */
		unsigned long bm_bits = drbd_bm_bits(device);
		unsigned long bit_pos;
		unsigned long long stop_sector = 0;
		if (state.conn == C_VERIFY_S ||
		    state.conn == C_VERIFY_T) {
			bit_pos = bm_bits - device->ov_left;
			if (verify_can_do_stop_sector(device))
				stop_sector = device->ov_stop_sector;
		} else
			bit_pos = device->bm_resync_fo;
		/* Total sectors may be slightly off for oddly
		 * sized devices. So what. */
		seq_printf(seq,
			"\t%3d%% sector pos: %llu/%llu",
			(int)(bit_pos / (bm_bits/100+1)),
			(unsigned long long)bit_pos * BM_SECT_PER_BIT,
			(unsigned long long)bm_bits * BM_SECT_PER_BIT);
		if (stop_sector != 0 && stop_sector != ULLONG_MAX)
			seq_printf(seq, " stop sector: %llu", stop_sector);
		seq_putc(seq, '\n');
	}
}