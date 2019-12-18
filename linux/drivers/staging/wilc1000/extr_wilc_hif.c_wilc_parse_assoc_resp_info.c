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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct wilc_conn_info {scalar_t__ resp_ies_len; int /*<<< orphan*/  resp_ies; int /*<<< orphan*/  status; } ;
struct assoc_resp {int /*<<< orphan*/  status_code; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  kmemdup (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 wilc_parse_assoc_resp_info(u8 *buffer, u32 buffer_len,
				      struct wilc_conn_info *ret_conn_info)
{
	u8 *ies;
	u16 ies_len;
	struct assoc_resp *res = (struct assoc_resp *)buffer;

	ret_conn_info->status = le16_to_cpu(res->status_code);
	if (ret_conn_info->status == WLAN_STATUS_SUCCESS) {
		ies = &buffer[sizeof(*res)];
		ies_len = buffer_len - sizeof(*res);

		ret_conn_info->resp_ies = kmemdup(ies, ies_len, GFP_KERNEL);
		if (!ret_conn_info->resp_ies)
			return -ENOMEM;

		ret_conn_info->resp_ies_len = ies_len;
	}

	return 0;
}