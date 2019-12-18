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
typedef  int u32 ;
struct icc_rpm_smd_req {int /*<<< orphan*/  value; int /*<<< orphan*/  nbytes; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int RPM_KEY_BW ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  icc_smd_rpm ; 
 int qcom_rpm_smd_write (int /*<<< orphan*/ ,int,int,int,struct icc_rpm_smd_req*,int) ; 

int qcom_icc_rpm_smd_send(int ctx, int rsc_type, int id, u32 val)
{
	struct icc_rpm_smd_req req = {
		.key = cpu_to_le32(RPM_KEY_BW),
		.nbytes = cpu_to_le32(sizeof(u32)),
		.value = cpu_to_le32(val),
	};

	return qcom_rpm_smd_write(icc_smd_rpm, ctx, rsc_type, id, &req,
				  sizeof(req));
}