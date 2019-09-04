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
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ opal_xive_get_vp_info (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int xive_native_get_vp_info(u32 vp_id, u32 *out_cam_id, u32 *out_chip_id)
{
	__be64 vp_cam_be;
	__be32 vp_chip_id_be;
	s64 rc;

	rc = opal_xive_get_vp_info(vp_id, NULL, &vp_cam_be, NULL, &vp_chip_id_be);
	if (rc)
		return -EIO;
	*out_cam_id = be64_to_cpu(vp_cam_be) & 0xffffffffu;
	*out_chip_id = be32_to_cpu(vp_chip_id_be);

	return 0;
}