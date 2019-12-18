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
struct gp2a_data {int /*<<< orphan*/  input; TYPE_1__* pdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  vout_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  SW_FRONT_PROXIMITY ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gp2a_report(struct gp2a_data *dt)
{
	int vo = gpio_get_value(dt->pdata->vout_gpio);

	input_report_switch(dt->input, SW_FRONT_PROXIMITY, !vo);
	input_sync(dt->input);

	return 0;
}