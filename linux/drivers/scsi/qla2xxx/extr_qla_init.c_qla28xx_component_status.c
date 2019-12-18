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
struct qla27xx_image_status {int dummy; } ;
struct TYPE_2__ {void* npiv_config_2_3; void* npiv_config_0_1; void* vpd_nvram; void* board_config; } ;
struct active_regions {TYPE_1__ aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLA28XX_AUX_IMG_BOARD_CONFIG ; 
 int /*<<< orphan*/  QLA28XX_AUX_IMG_NPIV_CONFIG_0_1 ; 
 int /*<<< orphan*/  QLA28XX_AUX_IMG_NPIV_CONFIG_2_3 ; 
 int /*<<< orphan*/  QLA28XX_AUX_IMG_VPD_NVRAM ; 
 void* qla28xx_component_bitmask (struct qla27xx_image_status*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qla28xx_component_status(
    struct active_regions *active_regions, struct qla27xx_image_status *aux)
{
	active_regions->aux.board_config =
	    qla28xx_component_bitmask(aux, QLA28XX_AUX_IMG_BOARD_CONFIG);

	active_regions->aux.vpd_nvram =
	    qla28xx_component_bitmask(aux, QLA28XX_AUX_IMG_VPD_NVRAM);

	active_regions->aux.npiv_config_0_1 =
	    qla28xx_component_bitmask(aux, QLA28XX_AUX_IMG_NPIV_CONFIG_0_1);

	active_regions->aux.npiv_config_2_3 =
	    qla28xx_component_bitmask(aux, QLA28XX_AUX_IMG_NPIV_CONFIG_2_3);
}