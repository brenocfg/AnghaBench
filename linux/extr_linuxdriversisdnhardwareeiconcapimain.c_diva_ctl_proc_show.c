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
struct seq_file {struct capi_ctr* private; } ;
struct capi_ctr {int /*<<< orphan*/  serial; int /*<<< orphan*/  name; scalar_t__ driverdata; } ;
struct TYPE_3__ {int /*<<< orphan*/  channels; } ;
struct TYPE_4__ {TYPE_1__ d; int /*<<< orphan*/  Id; } ;
typedef  TYPE_2__ diva_card ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int diva_ctl_proc_show(struct seq_file *m, void *v)
{
	struct capi_ctr *ctrl = m->private;
	diva_card *card = (diva_card *) ctrl->driverdata;

	seq_printf(m, "%s\n", ctrl->name);
	seq_printf(m, "Serial No. : %s\n", ctrl->serial);
	seq_printf(m, "Id         : %d\n", card->Id);
	seq_printf(m, "Channels   : %d\n", card->d.channels);

	return 0;
}