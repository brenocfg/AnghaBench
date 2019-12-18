#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_4__ {scalar_t__ data_id_rreg; int /*<<< orphan*/  data_selection_ctrl; } ;
struct TYPE_3__ {scalar_t__ code; } ;
struct mipid02_dev {TYPE_2__ r; TYPE_1__ fmt; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MEDIA_BUS_FMT_JPEG_1X8 ; 
 int /*<<< orphan*/  SELECTION_MANUAL_DATA ; 
 scalar_t__ data_type_from_code (scalar_t__) ; 

__attribute__((used)) static int mipid02_configure_from_code(struct mipid02_dev *bridge)
{
	u8 data_type;

	bridge->r.data_id_rreg = 0;

	if (bridge->fmt.code != MEDIA_BUS_FMT_JPEG_1X8) {
		bridge->r.data_selection_ctrl |= SELECTION_MANUAL_DATA;

		data_type = data_type_from_code(bridge->fmt.code);
		if (!data_type)
			return -EINVAL;
		bridge->r.data_id_rreg = data_type;
	}

	return 0;
}