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
struct displayid_hdr {int bytes; int /*<<< orphan*/  ext_count; int /*<<< orphan*/  prod_id; int /*<<< orphan*/  rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_NOTE (char*,scalar_t__) ; 
 int EINVAL ; 

__attribute__((used)) static int validate_displayid(u8 *displayid, int length, int idx)
{
	int i;
	u8 csum = 0;
	struct displayid_hdr *base;

	base = (struct displayid_hdr *)&displayid[idx];

	DRM_DEBUG_KMS("base revision 0x%x, length %d, %d %d\n",
		      base->rev, base->bytes, base->prod_id, base->ext_count);

	if (base->bytes + 5 > length - idx)
		return -EINVAL;
	for (i = idx; i <= base->bytes + 5; i++) {
		csum += displayid[i];
	}
	if (csum) {
		DRM_NOTE("DisplayID checksum invalid, remainder is %d\n", csum);
		return -EINVAL;
	}
	return 0;
}