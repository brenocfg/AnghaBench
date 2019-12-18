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
typedef  int /*<<< orphan*/  time64_t ;
struct tm {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
struct hwrm_fw_set_time_input {int /*<<< orphan*/  second; int /*<<< orphan*/  minute; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; scalar_t__ month; int /*<<< orphan*/  year; int /*<<< orphan*/  member_0; } ;
struct bnxt {int hwrm_spec_code; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 scalar_t__ BNXT_VF (struct bnxt*) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_FW_SET_TIME ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_fw_set_time_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_fw_set_time_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 int /*<<< orphan*/  time64_to_tm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tm*) ; 

int bnxt_hwrm_fw_set_time(struct bnxt *bp)
{
	struct hwrm_fw_set_time_input req = {0};
	struct tm tm;
	time64_t now = ktime_get_real_seconds();

	if ((BNXT_VF(bp) && bp->hwrm_spec_code < 0x10901) ||
	    bp->hwrm_spec_code < 0x10400)
		return -EOPNOTSUPP;

	time64_to_tm(now, 0, &tm);
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FW_SET_TIME, -1, -1);
	req.year = cpu_to_le16(1900 + tm.tm_year);
	req.month = 1 + tm.tm_mon;
	req.day = tm.tm_mday;
	req.hour = tm.tm_hour;
	req.minute = tm.tm_min;
	req.second = tm.tm_sec;
	return hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
}