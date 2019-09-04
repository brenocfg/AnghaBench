#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int f_mode; struct conf_writedata* private_data; TYPE_1__* f_cred; } ;
struct conf_writedata {scalar_t__ state; int /*<<< orphan*/  card; } ;
struct TYPE_6__ {int debug_flags; } ;
typedef  TYPE_2__ hysdn_card ;
struct TYPE_5__ {int /*<<< orphan*/  fsgid; int /*<<< orphan*/  fsuid; } ;

/* Variables and functions */
 scalar_t__ CONF_STATE_POF ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int LOG_PROC_ALL ; 
 int LOG_PROC_OPEN ; 
 TYPE_2__* PDE_DATA (struct inode*) ; 
 int /*<<< orphan*/  hysdn_addlog (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hysdn_conf_mutex ; 
 int /*<<< orphan*/  kfree (struct conf_writedata*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pof_write_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hysdn_conf_close(struct inode *ino, struct file *filep)
{
	hysdn_card *card;
	struct conf_writedata *cnf;
	int retval = 0;

	mutex_lock(&hysdn_conf_mutex);
	card = PDE_DATA(ino);
	if (card->debug_flags & (LOG_PROC_OPEN | LOG_PROC_ALL))
		hysdn_addlog(card, "config close for uid=%d gid=%d mode=0x%x",
			     filep->f_cred->fsuid, filep->f_cred->fsgid,
			     filep->f_mode);

	if ((filep->f_mode & (FMODE_READ | FMODE_WRITE)) == FMODE_WRITE) {
		/* write only access -> write boot file or conf line */
		if (filep->private_data) {
			cnf = filep->private_data;

			if (cnf->state == CONF_STATE_POF)
				retval = pof_write_close(cnf->card);	/* close the pof write */
			kfree(filep->private_data);	/* free allocated memory for buffer */

		}		/* handle write private data */
	} else if ((filep->f_mode & (FMODE_READ | FMODE_WRITE)) == FMODE_READ) {
		/* read access -> output card info data */

		kfree(filep->private_data);	/* release memory */
	}
	mutex_unlock(&hysdn_conf_mutex);
	return (retval);
}