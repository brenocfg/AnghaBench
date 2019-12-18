#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ u32 ;
struct imx319 {TYPE_2__* hflip; TYPE_1__* vflip; int /*<<< orphan*/  mutex; } ;
struct TYPE_6__ {size_t val; } ;
struct TYPE_5__ {size_t val; } ;

/* Variables and functions */
#define  MEDIA_BUS_FMT_SBGGR10_1X10 131 
#define  MEDIA_BUS_FMT_SGBRG10_1X10 130 
#define  MEDIA_BUS_FMT_SGRBG10_1X10 129 
#define  MEDIA_BUS_FMT_SRGGB10_1X10 128 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 imx319_get_format_code(struct imx319 *imx319)
{
	/*
	 * Only one bayer order is supported.
	 * It depends on the flip settings.
	 */
	u32 code;
	static const u32 codes[2][2] = {
		{ MEDIA_BUS_FMT_SRGGB10_1X10, MEDIA_BUS_FMT_SGRBG10_1X10, },
		{ MEDIA_BUS_FMT_SGBRG10_1X10, MEDIA_BUS_FMT_SBGGR10_1X10, },
	};

	lockdep_assert_held(&imx319->mutex);
	code = codes[imx319->vflip->val][imx319->hflip->val];

	return code;
}