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
struct m5mols_info {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_MODE ; 
 unsigned int REG_AE_ALL ; 
 unsigned int REG_AE_CENTER ; 
 unsigned int REG_AE_SPOT ; 
#define  V4L2_EXPOSURE_METERING_CENTER_WEIGHTED 129 
#define  V4L2_EXPOSURE_METERING_SPOT 128 
 int m5mols_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int m5mols_set_metering_mode(struct m5mols_info *info, int mode)
{
	unsigned int metering;

	switch (mode) {
	case V4L2_EXPOSURE_METERING_CENTER_WEIGHTED:
		metering = REG_AE_CENTER;
		break;
	case V4L2_EXPOSURE_METERING_SPOT:
		metering = REG_AE_SPOT;
		break;
	default:
		metering = REG_AE_ALL;
		break;
	}

	return m5mols_write(&info->sd, AE_MODE, metering);
}