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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct octeon_device {size_t octeon_id; int /*<<< orphan*/  chip_id; } ;
struct TYPE_2__ {int conf_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_210NV ; 
 int /*<<< orphan*/  LIO_410NV ; 
 int /*<<< orphan*/  OCTEON_CN23XX_PF_VID ; 
 int /*<<< orphan*/  OCTEON_CN23XX_VF_VID ; 
 int /*<<< orphan*/  OCTEON_CN66XX ; 
 int /*<<< orphan*/  OCTEON_CN68XX ; 
#define  OCTEON_CONFIG_TYPE_DEFAULT 128 
 int /*<<< orphan*/  default_cn23xx_conf ; 
 int /*<<< orphan*/  default_cn66xx_conf ; 
 int /*<<< orphan*/  default_cn68xx_210nv_conf ; 
 int /*<<< orphan*/  default_cn68xx_conf ; 
 TYPE_1__* oct_conf_info ; 

__attribute__((used)) static void *__retrieve_octeon_config_info(struct octeon_device *oct,
					   u16 card_type)
{
	u32 oct_id = oct->octeon_id;
	void *ret = NULL;

	switch (oct_conf_info[oct_id].conf_type) {
	case OCTEON_CONFIG_TYPE_DEFAULT:
		if (oct->chip_id == OCTEON_CN66XX) {
			ret = &default_cn66xx_conf;
		} else if ((oct->chip_id == OCTEON_CN68XX) &&
			   (card_type == LIO_210NV)) {
			ret = &default_cn68xx_210nv_conf;
		} else if ((oct->chip_id == OCTEON_CN68XX) &&
			   (card_type == LIO_410NV)) {
			ret = &default_cn68xx_conf;
		} else if (oct->chip_id == OCTEON_CN23XX_PF_VID) {
			ret = &default_cn23xx_conf;
		} else if (oct->chip_id == OCTEON_CN23XX_VF_VID) {
			ret = &default_cn23xx_conf;
		}
		break;
	default:
		break;
	}
	return ret;
}