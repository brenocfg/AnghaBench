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
struct mcam_camera {int /*<<< orphan*/  dev_lock; int /*<<< orphan*/  (* dma_setup ) (struct mcam_camera*) ;int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_SG_RESTART ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcam_ctlr_image (struct mcam_camera*) ; 
 int /*<<< orphan*/  mcam_set_config_needed (struct mcam_camera*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct mcam_camera*) ; 

__attribute__((used)) static int mcam_ctlr_configure(struct mcam_camera *cam)
{
	unsigned long flags;

	spin_lock_irqsave(&cam->dev_lock, flags);
	clear_bit(CF_SG_RESTART, &cam->flags);
	cam->dma_setup(cam);
	mcam_ctlr_image(cam);
	mcam_set_config_needed(cam, 0);
	spin_unlock_irqrestore(&cam->dev_lock, flags);
	return 0;
}