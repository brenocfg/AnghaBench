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
struct TYPE_2__ {int /*<<< orphan*/ * plt_config; int /*<<< orphan*/ * telem_ops; } ;

/* Variables and functions */
 TYPE_1__ telm_core_conf ; 
 int /*<<< orphan*/  telm_defpltops ; 

int telemetry_clear_pltdata(void)
{
	telm_core_conf.telem_ops = &telm_defpltops;
	telm_core_conf.plt_config = NULL;

	return 0;
}