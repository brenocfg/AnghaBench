#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct procdata {int /*<<< orphan*/  rd_queue; int /*<<< orphan*/  log_name; int /*<<< orphan*/  log; } ;
struct TYPE_4__ {void* proclog; int /*<<< orphan*/  myid; } ;
typedef  TYPE_1__ hysdn_card ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* PROC_LOG_BASENAME ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  hysdn_proc_entry ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct procdata* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_fops ; 
 int /*<<< orphan*/  proc_create_data (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

int
hysdn_proclog_init(hysdn_card *card)
{
	struct procdata *pd;

	/* create a cardlog proc entry */

	if ((pd = kzalloc(sizeof(struct procdata), GFP_KERNEL)) != NULL) {
		sprintf(pd->log_name, "%s%d", PROC_LOG_BASENAME, card->myid);
		pd->log = proc_create_data(pd->log_name,
				      S_IFREG | S_IRUGO | S_IWUSR, hysdn_proc_entry,
				      &log_fops, card);

		init_waitqueue_head(&(pd->rd_queue));

		card->proclog = (void *) pd;	/* remember procfs structure */
	}
	return (0);
}