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
typedef  unsigned long long u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct hfi1_devdata {int /*<<< orphan*/ * send_err_status_cnt; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int NUM_SEND_ERR_STATUS_COUNTERS ; 
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  incr_cntr64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_err_status_string (char*,int,unsigned long long) ; 

__attribute__((used)) static void handle_txe_err(struct hfi1_devdata *dd, u32 unused, u64 reg)
{
	char buf[96];
	int i = 0;

	dd_dev_info(dd, "Send Error: %s\n",
		    send_err_status_string(buf, sizeof(buf), reg));

	for (i = 0; i < NUM_SEND_ERR_STATUS_COUNTERS; i++) {
		if (reg & (1ull << i))
			incr_cntr64(&dd->send_err_status_cnt[i]);
	}
}