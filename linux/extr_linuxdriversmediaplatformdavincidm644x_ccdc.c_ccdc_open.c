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
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ if_type; } ;

/* Variables and functions */
 scalar_t__ VPFE_RAW_BAYER ; 
 TYPE_1__ ccdc_cfg ; 
 int /*<<< orphan*/  ccdc_enable_vport (int) ; 
 int /*<<< orphan*/  ccdc_restore_defaults () ; 

__attribute__((used)) static int ccdc_open(struct device *device)
{
	ccdc_restore_defaults();
	if (ccdc_cfg.if_type == VPFE_RAW_BAYER)
		ccdc_enable_vport(1);
	return 0;
}