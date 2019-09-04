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
struct speed_down_verdict_arg {scalar_t__ since; int /*<<< orphan*/ * nr_errors; int /*<<< orphan*/  xfer_ok; } ;
struct ata_ering_entry {int eflags; scalar_t__ timestamp; int /*<<< orphan*/  err_mask; } ;

/* Variables and functions */
 int ATA_EFLAG_OLD_ER ; 
 int ata_eh_categorize_error (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int speed_down_verdict_cb(struct ata_ering_entry *ent, void *void_arg)
{
	struct speed_down_verdict_arg *arg = void_arg;
	int cat;

	if ((ent->eflags & ATA_EFLAG_OLD_ER) || (ent->timestamp < arg->since))
		return -1;

	cat = ata_eh_categorize_error(ent->eflags, ent->err_mask,
				      &arg->xfer_ok);
	arg->nr_errors[cat]++;

	return 0;
}