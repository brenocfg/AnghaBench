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
struct ata_queued_cmd {int /*<<< orphan*/  result_tf; TYPE_2__* ap; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* sff_tf_read ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 

bool ata_sff_qc_fill_rtf(struct ata_queued_cmd *qc)
{
	qc->ap->ops->sff_tf_read(qc->ap, &qc->result_tf);
	return true;
}