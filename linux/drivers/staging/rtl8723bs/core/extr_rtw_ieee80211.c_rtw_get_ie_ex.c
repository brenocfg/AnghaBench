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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (scalar_t__*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,scalar_t__) ; 

u8 *rtw_get_ie_ex(u8 *in_ie, uint in_len, u8 eid, u8 *oui, u8 oui_len, u8 *ie, uint *ielen)
{
	uint cnt;
	u8 *target_ie = NULL;

	if (ielen)
		*ielen = 0;

	if (!in_ie || in_len <= 0)
		return target_ie;

	cnt = 0;

	while (cnt < in_len) {
		if (eid == in_ie[cnt]
			&& (!oui || !memcmp(&in_ie[cnt+2], oui, oui_len))) {
			target_ie = &in_ie[cnt];

			if (ie)
				memcpy(ie, &in_ie[cnt], in_ie[cnt+1]+2);

			if (ielen)
				*ielen = in_ie[cnt+1]+2;

			break;
		} else {
			cnt += in_ie[cnt+1]+2; /* goto next */
		}
	}

	return target_ie;
}