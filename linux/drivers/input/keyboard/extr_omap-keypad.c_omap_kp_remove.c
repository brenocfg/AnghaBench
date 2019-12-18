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
struct platform_device {int dummy; } ;
struct omap_kp {int /*<<< orphan*/  input; int /*<<< orphan*/  timer; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ OMAP1_MPUIO_BASE ; 
 scalar_t__ OMAP_MPUIO_KBD_MASKIT ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct omap_kp*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct omap_kp*) ; 
 int /*<<< orphan*/  kp_tasklet ; 
 int /*<<< orphan*/  omap_writew (int,scalar_t__) ; 
 struct omap_kp* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_kp_remove(struct platform_device *pdev)
{
	struct omap_kp *omap_kp = platform_get_drvdata(pdev);

	/* disable keypad interrupt handling */
	tasklet_disable(&kp_tasklet);
	omap_writew(1, OMAP1_MPUIO_BASE + OMAP_MPUIO_KBD_MASKIT);
	free_irq(omap_kp->irq, omap_kp);

	del_timer_sync(&omap_kp->timer);
	tasklet_kill(&kp_tasklet);

	/* unregister everything */
	input_unregister_device(omap_kp->input);

	kfree(omap_kp);

	return 0;
}