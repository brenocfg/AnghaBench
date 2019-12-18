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
struct vfio_ccw_private {int dummy; } ;
struct subchannel {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQIO_CIO ; 
 int /*<<< orphan*/  VFIO_CCW_EVENT_INTERRUPT ; 
 struct vfio_ccw_private* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_ccw_fsm_event (struct vfio_ccw_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vfio_ccw_sch_irq(struct subchannel *sch)
{
	struct vfio_ccw_private *private = dev_get_drvdata(&sch->dev);

	inc_irq_stat(IRQIO_CIO);
	vfio_ccw_fsm_event(private, VFIO_CCW_EVENT_INTERRUPT);
}