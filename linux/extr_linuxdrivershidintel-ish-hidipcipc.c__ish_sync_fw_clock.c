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
typedef  int /*<<< orphan*/  uint64_t ;
struct ishtp_device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  MNG_SYNC_FW_CLOCK ; 
 int /*<<< orphan*/  ipc_send_mng_msg (struct ishtp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  ktime_get_boottime () ; 
 int /*<<< orphan*/  ktime_to_us (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _ish_sync_fw_clock(struct ishtp_device *dev)
{
	static unsigned long	prev_sync;
	uint64_t	usec;

	if (prev_sync && jiffies - prev_sync < 20 * HZ)
		return;

	prev_sync = jiffies;
	usec = ktime_to_us(ktime_get_boottime());
	ipc_send_mng_msg(dev, MNG_SYNC_FW_CLOCK, &usec, sizeof(uint64_t));
}