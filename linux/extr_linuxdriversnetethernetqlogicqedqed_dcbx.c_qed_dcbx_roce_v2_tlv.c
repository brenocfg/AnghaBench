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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int /*<<< orphan*/  DCBX_APP_SF_IEEE_UDP_PORT ; 
 scalar_t__ QED_UDP_PORT_TYPE_ROCE_V2 ; 
 int qed_dcbx_app_port (int /*<<< orphan*/ ) ; 
 int qed_dcbx_ieee_app_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool qed_dcbx_roce_v2_tlv(u32 app_info_bitmap, u16 proto_id, bool ieee)
{
	bool port;

	if (ieee)
		port = qed_dcbx_ieee_app_port(app_info_bitmap,
					      DCBX_APP_SF_IEEE_UDP_PORT);
	else
		port = qed_dcbx_app_port(app_info_bitmap);

	return !!(port && (proto_id == QED_UDP_PORT_TYPE_ROCE_V2));
}