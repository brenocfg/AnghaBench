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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct qed_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_NUM_PFS ; 
 int /*<<< orphan*/  PXP_CONCRETE_FID_PFID ; 
 int /*<<< orphan*/  PXP_CONCRETE_FID_VFID ; 
 int /*<<< orphan*/  PXP_CONCRETE_FID_VFVALID ; 

__attribute__((used)) static inline u8 qed_concrete_to_sw_fid(struct qed_dev *cdev,
					u32 concrete_fid)
{
	u8 vfid = GET_FIELD(concrete_fid, PXP_CONCRETE_FID_VFID);
	u8 pfid = GET_FIELD(concrete_fid, PXP_CONCRETE_FID_PFID);
	u8 vf_valid = GET_FIELD(concrete_fid,
				PXP_CONCRETE_FID_VFVALID);
	u8 sw_fid;

	if (vf_valid)
		sw_fid = vfid + MAX_NUM_PFS;
	else
		sw_fid = pfid;

	return sw_fid;
}