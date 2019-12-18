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
struct nvmet_fc_target_port {int /*<<< orphan*/  private; } ;
struct fcloop_rscn {int /*<<< orphan*/  work; int /*<<< orphan*/  tport; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcloop_tgt_rscn_work ; 
 struct fcloop_rscn* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fcloop_tgt_discovery_evt(struct nvmet_fc_target_port *tgtport)
{
	struct fcloop_rscn *tgt_rscn;

	tgt_rscn = kzalloc(sizeof(*tgt_rscn), GFP_KERNEL);
	if (!tgt_rscn)
		return;

	tgt_rscn->tport = tgtport->private;
	INIT_WORK(&tgt_rscn->work, fcloop_tgt_rscn_work);

	schedule_work(&tgt_rscn->work);
}