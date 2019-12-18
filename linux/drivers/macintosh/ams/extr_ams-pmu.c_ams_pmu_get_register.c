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
typedef  int /*<<< orphan*/  u8 ;
struct adb_request {scalar_t__ reply_len; int /*<<< orphan*/ * reply; int /*<<< orphan*/ * arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ams_pmu_cmd ; 
 int /*<<< orphan*/  ams_pmu_req_complete ; 
 scalar_t__ pmu_request (struct adb_request*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  req_complete ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 ams_pmu_get_register(u8 reg)
{
	static struct adb_request req;
	DECLARE_COMPLETION(req_complete);

	req.arg = &req_complete;
	if (pmu_request(&req, ams_pmu_req_complete, 3, ams_pmu_cmd, 0x01, reg))
		return 0;

	wait_for_completion(&req_complete);

	if (req.reply_len > 0)
		return req.reply[0];
	else
		return 0;
}