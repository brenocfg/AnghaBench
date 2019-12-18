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
typedef  int /*<<< orphan*/  u8 ;
struct seq_file {int dummy; } ;
struct TYPE_4__ {int phase; int /*<<< orphan*/  buffer; int /*<<< orphan*/  this_residual; } ;
struct scsi_cmnd {TYPE_2__ SCp; int /*<<< orphan*/ * cmnd; TYPE_1__* device; } ;
struct TYPE_3__ {scalar_t__ lun; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int COMMAND_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCNEXT (struct scsi_cmnd*) ; 
 int aborted ; 
 int completed ; 
 int disconnected ; 
 int identified ; 
 int not_issued ; 
 int /*<<< orphan*/  scsi_get_resid (struct scsi_cmnd*) ; 
 int selecting ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,struct scsi_cmnd*,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 scalar_t__ sg_nents (int /*<<< orphan*/ ) ; 
 int spiordy ; 
 int syncneg ; 

__attribute__((used)) static void get_command(struct seq_file *m, struct scsi_cmnd * ptr)
{
	int i;

	seq_printf(m, "%p: target=%d; lun=%d; cmnd=( ",
		ptr, ptr->device->id, (u8)ptr->device->lun);

	for (i = 0; i < COMMAND_SIZE(ptr->cmnd[0]); i++)
		seq_printf(m, "0x%02x ", ptr->cmnd[i]);

	seq_printf(m, "); resid=%d; residual=%d; buffers=%d; phase |",
		scsi_get_resid(ptr), ptr->SCp.this_residual,
		sg_nents(ptr->SCp.buffer) - 1);

	if (ptr->SCp.phase & not_issued)
		seq_puts(m, "not issued|");
	if (ptr->SCp.phase & selecting)
		seq_puts(m, "selecting|");
	if (ptr->SCp.phase & disconnected)
		seq_puts(m, "disconnected|");
	if (ptr->SCp.phase & aborted)
		seq_puts(m, "aborted|");
	if (ptr->SCp.phase & identified)
		seq_puts(m, "identified|");
	if (ptr->SCp.phase & completed)
		seq_puts(m, "completed|");
	if (ptr->SCp.phase & spiordy)
		seq_puts(m, "spiordy|");
	if (ptr->SCp.phase & syncneg)
		seq_puts(m, "syncneg|");
	seq_printf(m, "; next=0x%p\n", SCNEXT(ptr));
}