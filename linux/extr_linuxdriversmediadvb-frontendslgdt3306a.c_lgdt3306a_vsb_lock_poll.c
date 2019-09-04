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
typedef  int u8 ;
typedef  int u32 ;
struct lgdt3306a_state {int dummy; } ;
typedef  enum lgdt3306a_lock_status { ____Placeholder_lgdt3306a_lock_status } lgdt3306a_lock_status ;

/* Variables and functions */
 int LG3306_LOCK ; 
 scalar_t__ LG3306_UNLOCK ; 
 int /*<<< orphan*/  dbg_info (char*,...) ; 
 int lgdt3306a_calculate_snr_x100 (struct lgdt3306a_state*) ; 
 int lgdt3306a_get_packet_error (struct lgdt3306a_state*) ; 
 int lgdt3306a_pre_monitoring (struct lgdt3306a_state*) ; 
 scalar_t__ lgdt3306a_sync_lock_poll (struct lgdt3306a_state*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static enum lgdt3306a_lock_status
lgdt3306a_vsb_lock_poll(struct lgdt3306a_state *state)
{
	int ret;
	u8 cnt = 0;
	u8 packet_error;
	u32 snr;

	for (cnt = 0; cnt < 10; cnt++) {
		if (lgdt3306a_sync_lock_poll(state) == LG3306_UNLOCK) {
			dbg_info("no sync lock!\n");
			return LG3306_UNLOCK;
		}

		msleep(20);
		ret = lgdt3306a_pre_monitoring(state);
		if (ret)
			break;

		packet_error = lgdt3306a_get_packet_error(state);
		snr = lgdt3306a_calculate_snr_x100(state);
		dbg_info("cnt=%d errors=%d snr=%d\n", cnt, packet_error, snr);

		if ((snr >= 1500) && (packet_error < 0xff))
			return LG3306_LOCK;
	}

	dbg_info("not locked!\n");
	return LG3306_UNLOCK;
}