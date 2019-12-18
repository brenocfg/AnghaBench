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
struct octeon_device {int chip_id; } ;

/* Variables and functions */
#define  OCTEON_CN23XX_PF_VID 131 
#define  OCTEON_CN23XX_VF_VID 130 
#define  OCTEON_CN66XX 129 
#define  OCTEON_CN68XX 128 
 int lio_validate_cn6xxx_config_info (struct octeon_device*,void*) ; 

__attribute__((used)) static int __verify_octeon_config_info(struct octeon_device *oct, void *conf)
{
	switch (oct->chip_id) {
	case OCTEON_CN66XX:
	case OCTEON_CN68XX:
		return lio_validate_cn6xxx_config_info(oct, conf);
	case OCTEON_CN23XX_PF_VID:
	case OCTEON_CN23XX_VF_VID:
		return 0;
	default:
		break;
	}

	return 1;
}