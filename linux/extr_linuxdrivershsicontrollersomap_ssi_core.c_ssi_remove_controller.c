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
struct omap_ssi_controller {int /*<<< orphan*/  fck_nb; int /*<<< orphan*/  fck; int /*<<< orphan*/  gdd_tasklet; } ;
struct hsi_controller {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_notifier_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct omap_ssi_controller* hsi_controller_drvdata (struct hsi_controller*) ; 
 int /*<<< orphan*/  hsi_unregister_controller (struct hsi_controller*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  platform_omap_ssi_ida ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ssi_remove_controller(struct hsi_controller *ssi)
{
	struct omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	int id = ssi->id;
	tasklet_kill(&omap_ssi->gdd_tasklet);
	hsi_unregister_controller(ssi);
	clk_notifier_unregister(omap_ssi->fck, &omap_ssi->fck_nb);
	ida_simple_remove(&platform_omap_ssi_ida, id);
}