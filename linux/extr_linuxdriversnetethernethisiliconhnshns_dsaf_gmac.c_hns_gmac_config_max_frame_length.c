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
typedef  int /*<<< orphan*/  u16 ;
struct mac_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAMC_RX_MAX_FRAME ; 
 int /*<<< orphan*/  GMAC_MAX_FRM_SIZE_M ; 
 int /*<<< orphan*/  GMAC_MAX_FRM_SIZE_REG ; 
 int /*<<< orphan*/  GMAC_MAX_FRM_SIZE_S ; 
 int /*<<< orphan*/  dsaf_set_dev_field (struct mac_driver*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_gmac_config_max_frame_length(void *mac_drv, u16 newval)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	dsaf_set_dev_field(drv, GMAC_MAX_FRM_SIZE_REG, GMAC_MAX_FRM_SIZE_M,
			   GMAC_MAX_FRM_SIZE_S, newval);

	dsaf_set_dev_field(drv, GAMC_RX_MAX_FRAME, GMAC_MAX_FRM_SIZE_M,
			   GMAC_MAX_FRM_SIZE_S, newval);
}