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
struct scsi_tape {int index; int /*<<< orphan*/  kref; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct scsi_tape* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_cdevs (struct scsi_tape*) ; 
 int /*<<< orphan*/  scsi_autopm_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_tape_release ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st_index_idr ; 
 int /*<<< orphan*/  st_index_lock ; 
 int /*<<< orphan*/  st_ref_mutex ; 
 int /*<<< orphan*/  to_scsi_device (struct device*) ; 

__attribute__((used)) static int st_remove(struct device *dev)
{
	struct scsi_tape *tpnt = dev_get_drvdata(dev);
	int index = tpnt->index;

	scsi_autopm_get_device(to_scsi_device(dev));
	remove_cdevs(tpnt);

	mutex_lock(&st_ref_mutex);
	kref_put(&tpnt->kref, scsi_tape_release);
	mutex_unlock(&st_ref_mutex);
	spin_lock(&st_index_lock);
	idr_remove(&st_index_idr, index);
	spin_unlock(&st_index_lock);
	return 0;
}