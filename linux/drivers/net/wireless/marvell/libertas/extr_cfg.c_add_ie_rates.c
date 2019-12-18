#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int bitrate; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  LBS_DEB_ASSOC ; 
 int /*<<< orphan*/  lbs_deb_hex (int /*<<< orphan*/ ,char*,int*,int) ; 
 TYPE_1__* lbs_rates ; 

__attribute__((used)) static u8 *
add_ie_rates(u8 *tlv, const u8 *ie, int *nrates)
{
	int hw, ap, ap_max = ie[1];
	u8 hw_rate;

	/* Advance past IE header */
	ie += 2;

	lbs_deb_hex(LBS_DEB_ASSOC, "AP IE Rates", (u8 *) ie, ap_max);

	for (hw = 0; hw < ARRAY_SIZE(lbs_rates); hw++) {
		hw_rate = lbs_rates[hw].bitrate / 5;
		for (ap = 0; ap < ap_max; ap++) {
			if (hw_rate == (ie[ap] & 0x7f)) {
				*tlv++ = ie[ap];
				*nrates = *nrates + 1;
			}
		}
	}
	return tlv;
}