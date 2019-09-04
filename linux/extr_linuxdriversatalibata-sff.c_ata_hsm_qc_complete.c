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
struct ata_queued_cmd {int err_mask; int /*<<< orphan*/  tag; struct ata_port* ap; } ;
struct ata_port {TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ error_handler; } ;

/* Variables and functions */
 int AC_ERR_HSM ; 
 int /*<<< orphan*/  ata_port_freeze (struct ata_port*) ; 
 int /*<<< orphan*/  ata_qc_complete (struct ata_queued_cmd*) ; 
 struct ata_queued_cmd* ata_qc_from_tag (struct ata_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_sff_irq_on (struct ata_port*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static void ata_hsm_qc_complete(struct ata_queued_cmd *qc, int in_wq)
{
	struct ata_port *ap = qc->ap;

	if (ap->ops->error_handler) {
		if (in_wq) {
			/* EH might have kicked in while host lock is
			 * released.
			 */
			qc = ata_qc_from_tag(ap, qc->tag);
			if (qc) {
				if (likely(!(qc->err_mask & AC_ERR_HSM))) {
					ata_sff_irq_on(ap);
					ata_qc_complete(qc);
				} else
					ata_port_freeze(ap);
			}
		} else {
			if (likely(!(qc->err_mask & AC_ERR_HSM)))
				ata_qc_complete(qc);
			else
				ata_port_freeze(ap);
		}
	} else {
		if (in_wq) {
			ata_sff_irq_on(ap);
			ata_qc_complete(qc);
		} else
			ata_qc_complete(qc);
	}
}