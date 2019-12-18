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
struct rtw_sec_desc {int /*<<< orphan*/  cam_map; scalar_t__ default_key_search; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTW_MAX_SEC_CAM_NUM ; 
 int /*<<< orphan*/  RTW_SEC_DEFAULT_KEY_NUM ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int find_next_zero_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rtw_sec_get_free_cam(struct rtw_sec_desc *sec)
{
	/* if default key search is enabled, the first 4 cam entries
	 * are used to direct map to group key with its key->key_idx, so
	 * driver should use cam entries after 4 to install pairwise key
	 */
	if (sec->default_key_search)
		return find_next_zero_bit(sec->cam_map, RTW_MAX_SEC_CAM_NUM,
					  RTW_SEC_DEFAULT_KEY_NUM);

	return find_first_zero_bit(sec->cam_map, RTW_MAX_SEC_CAM_NUM);
}