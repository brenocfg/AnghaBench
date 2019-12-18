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
typedef  scalar_t__ uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * rtw_get_wps_attr (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 

u8 *rtw_get_wps_attr_content(u8 *wps_ie, uint wps_ielen, u16 target_attr_id, u8 *buf_content, uint *len_content)
{
	u8 *attr_ptr;
	u32 attr_len;

	if (len_content)
		*len_content = 0;

	attr_ptr = rtw_get_wps_attr(wps_ie, wps_ielen, target_attr_id, NULL, &attr_len);

	if (attr_ptr && attr_len) {
		if (buf_content)
			memcpy(buf_content, attr_ptr + 4, attr_len - 4);

		if (len_content)
			*len_content = attr_len - 4;

		return attr_ptr + 4;
	}

	return NULL;
}