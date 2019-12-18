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
struct ti_bandgap {int /*<<< orphan*/  tshut_gpio; int /*<<< orphan*/  irq; int /*<<< orphan*/  div_clk; int /*<<< orphan*/  fclock; TYPE_2__* conf; } ;
struct platform_device {int dummy; } ;
struct TYPE_4__ {int sensor_count; int /*<<< orphan*/  (* remove_sensor ) (struct ti_bandgap*,int) ;TYPE_1__* sensors; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* unregister_cooling ) (struct ti_bandgap*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_CTRL ; 
 int /*<<< orphan*/  TALERT ; 
 scalar_t__ TI_BANDGAP_HAS (struct ti_bandgap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSHUT ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ti_bandgap*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 struct ti_bandgap* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct ti_bandgap*,int) ; 
 int /*<<< orphan*/  stub2 (struct ti_bandgap*,int) ; 
 int /*<<< orphan*/  ti_bandgap_power (struct ti_bandgap*,int) ; 

__attribute__((used)) static
int ti_bandgap_remove(struct platform_device *pdev)
{
	struct ti_bandgap *bgp = platform_get_drvdata(pdev);
	int i;

	/* First thing is to remove sensor interfaces */
	for (i = 0; i < bgp->conf->sensor_count; i++) {
		if (bgp->conf->sensors[i].unregister_cooling)
			bgp->conf->sensors[i].unregister_cooling(bgp, i);

		if (bgp->conf->remove_sensor)
			bgp->conf->remove_sensor(bgp, i);
	}

	ti_bandgap_power(bgp, false);

	if (TI_BANDGAP_HAS(bgp, CLK_CTRL))
		clk_disable_unprepare(bgp->fclock);
	clk_put(bgp->fclock);
	clk_put(bgp->div_clk);

	if (TI_BANDGAP_HAS(bgp, TALERT))
		free_irq(bgp->irq, bgp);

	if (TI_BANDGAP_HAS(bgp, TSHUT)) {
		free_irq(gpio_to_irq(bgp->tshut_gpio), NULL);
		gpio_free(bgp->tshut_gpio);
	}

	return 0;
}