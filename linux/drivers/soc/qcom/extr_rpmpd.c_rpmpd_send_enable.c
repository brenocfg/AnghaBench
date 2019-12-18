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
typedef  int /*<<< orphan*/  u32 ;
struct rpmpd_req {int /*<<< orphan*/  value; int /*<<< orphan*/  nbytes; int /*<<< orphan*/  key; } ;
struct rpmpd {int /*<<< orphan*/  res_id; int /*<<< orphan*/  res_type; int /*<<< orphan*/  rpm; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_ENABLE ; 
 int /*<<< orphan*/  QCOM_SMD_RPM_ACTIVE_STATE ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int qcom_rpm_smd_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rpmpd_req*,int) ; 

__attribute__((used)) static int rpmpd_send_enable(struct rpmpd *pd, bool enable)
{
	struct rpmpd_req req = {
		.key = KEY_ENABLE,
		.nbytes = cpu_to_le32(sizeof(u32)),
		.value = cpu_to_le32(enable),
	};

	return qcom_rpm_smd_write(pd->rpm, QCOM_SMD_RPM_ACTIVE_STATE,
				  pd->res_type, pd->res_id, &req, sizeof(req));
}