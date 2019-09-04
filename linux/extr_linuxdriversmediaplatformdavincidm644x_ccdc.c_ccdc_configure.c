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
struct TYPE_2__ {scalar_t__ if_type; } ;

/* Variables and functions */
 scalar_t__ VPFE_RAW_BAYER ; 
 TYPE_1__ ccdc_cfg ; 
 int /*<<< orphan*/  ccdc_config_raw () ; 
 int /*<<< orphan*/  ccdc_config_ycbcr () ; 

__attribute__((used)) static int ccdc_configure(void)
{
	if (ccdc_cfg.if_type == VPFE_RAW_BAYER)
		ccdc_config_raw();
	else
		ccdc_config_ycbcr();
	return 0;
}