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
struct TYPE_2__ {int phase; } ;
struct scsi_cmnd {TYPE_1__ SCp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 scalar_t__ SCDATA (struct scsi_cmnd*) ; 
 int /*<<< orphan*/ * SCNEXT (struct scsi_cmnd*) ; 
 int aborted ; 
 int completed ; 
 int disconnected ; 
 int identified ; 
 int not_issued ; 
 int resetted ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_get_resid (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_print_command (struct scsi_cmnd*) ; 
 int selecting ; 
 int spiordy ; 
 int syncneg ; 

__attribute__((used)) static void show_command(struct scsi_cmnd *ptr)
{
	scsi_print_command(ptr);
	scmd_printk(KERN_DEBUG, ptr,
		    "request_bufflen=%d; resid=%d; "
		    "phase |%s%s%s%s%s%s%s%s%s; next=0x%p",
		    scsi_bufflen(ptr), scsi_get_resid(ptr),
		    (ptr->SCp.phase & not_issued) ? "not issued|" : "",
		    (ptr->SCp.phase & selecting) ? "selecting|" : "",
		    (ptr->SCp.phase & identified) ? "identified|" : "",
		    (ptr->SCp.phase & disconnected) ? "disconnected|" : "",
		    (ptr->SCp.phase & completed) ? "completed|" : "",
		    (ptr->SCp.phase & spiordy) ? "spiordy|" : "",
		    (ptr->SCp.phase & syncneg) ? "syncneg|" : "",
		    (ptr->SCp.phase & aborted) ? "aborted|" : "",
		    (ptr->SCp.phase & resetted) ? "resetted|" : "",
		    (SCDATA(ptr)) ? SCNEXT(ptr) : NULL);
}