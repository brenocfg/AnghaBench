#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct radeon_cs_parser {TYPE_1__* rdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_PALM ; 
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int) ; 
 int EINVAL ; 

__attribute__((used)) static int radeon_uvd_validate_codec(struct radeon_cs_parser *p,
				     unsigned stream_type)
{
	switch (stream_type) {
	case 0: /* H264 */
	case 1: /* VC1 */
		/* always supported */
		return 0;

	case 3: /* MPEG2 */
	case 4: /* MPEG4 */
		/* only since UVD 3 */
		if (p->rdev->family >= CHIP_PALM)
			return 0;

		/* fall through */
	default:
		DRM_ERROR("UVD codec not supported by hardware %d!\n",
			  stream_type);
		return -EINVAL;
	}
}