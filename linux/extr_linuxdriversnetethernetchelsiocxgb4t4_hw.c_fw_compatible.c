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
struct fw_hdr {scalar_t__ chip; scalar_t__ fw_ver; scalar_t__ intfver_nic; scalar_t__ intfver_vnic; scalar_t__ intfver_ri; scalar_t__ intfver_iscsi; scalar_t__ intfver_fcoe; } ;

/* Variables and functions */

__attribute__((used)) static int fw_compatible(const struct fw_hdr *hdr1, const struct fw_hdr *hdr2)
{

	/* short circuit if it's the exact same firmware version */
	if (hdr1->chip == hdr2->chip && hdr1->fw_ver == hdr2->fw_ver)
		return 1;

#define SAME_INTF(x) (hdr1->intfver_##x == hdr2->intfver_##x)
	if (hdr1->chip == hdr2->chip && SAME_INTF(nic) && SAME_INTF(vnic) &&
	    SAME_INTF(ri) && SAME_INTF(iscsi) && SAME_INTF(fcoe))
		return 1;
#undef SAME_INTF

	return 0;
}