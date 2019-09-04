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
struct malidp_drm {int /*<<< orphan*/  wq; } ;
struct drm_device {struct malidp_drm* dev_private; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t malidp_de_irq_thread_handler(int irq, void *arg)
{
	struct drm_device *drm = arg;
	struct malidp_drm *malidp = drm->dev_private;

	wake_up(&malidp->wq);

	return IRQ_HANDLED;
}