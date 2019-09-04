#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct procdata {scalar_t__ if_used; struct log_data* log_head; } ;
struct log_data {struct log_data* next; int /*<<< orphan*/  usage_cnt; scalar_t__ proc_ctrl; } ;
struct inode {int dummy; } ;
struct file {int f_mode; scalar_t__ private_data; } ;
struct TYPE_3__ {struct procdata* proclog; } ;
typedef  TYPE_1__ hysdn_card ;

/* Variables and functions */
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 TYPE_1__* PDE_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  hysdn_log_mutex ; 
 int /*<<< orphan*/  kfree (struct log_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hysdn_log_close(struct inode *ino, struct file *filep)
{
	struct log_data *inf;
	struct procdata *pd;
	hysdn_card *card;
	int retval = 0;

	mutex_lock(&hysdn_log_mutex);
	if ((filep->f_mode & (FMODE_READ | FMODE_WRITE)) == FMODE_WRITE) {
		/* write only access -> write debug level written */
		retval = 0;	/* success */
	} else {
		/* read access -> log/debug read, mark one further file as closed */

		inf = *((struct log_data **) filep->private_data);	/* get first log entry */
		if (inf)
			pd = (struct procdata *) inf->proc_ctrl;	/* still entries there */
		else {
			/* no info available -> search card */
			card = PDE_DATA(file_inode(filep));
			pd = card->proclog;	/* pointer to procfs log */
		}
		if (pd)
			pd->if_used--;	/* decrement interface usage count by one */

		while (inf) {
			inf->usage_cnt--;	/* decrement usage count for buffers */
			inf = inf->next;
		}

		if (pd)
			if (pd->if_used <= 0)	/* delete buffers if last file closed */
				while (pd->log_head) {
					inf = pd->log_head;
					pd->log_head = pd->log_head->next;
					kfree(inf);
				}
	}			/* read access */
	mutex_unlock(&hysdn_log_mutex);

	return (retval);
}