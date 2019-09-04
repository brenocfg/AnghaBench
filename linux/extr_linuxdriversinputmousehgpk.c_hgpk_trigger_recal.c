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
struct psmouse {struct hgpk_data* private; } ;
struct hgpk_data {int /*<<< orphan*/  recalib_wq; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int kstrtouint (char const*,int,unsigned int*) ; 
 int /*<<< orphan*/  psmouse_queue_work (struct psmouse*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t hgpk_trigger_recal(struct psmouse *psmouse, void *data,
				const char *buf, size_t count)
{
	struct hgpk_data *priv = psmouse->private;
	unsigned int value;
	int err;

	err = kstrtouint(buf, 10, &value);
	if (err)
		return err;

	if (value != 1)
		return -EINVAL;

	/*
	 * We queue work instead of doing recalibration right here
	 * to avoid adding locking to to hgpk_force_recalibrate()
	 * since workqueue provides serialization.
	 */
	psmouse_queue_work(psmouse, &priv->recalib_wq, 0);
	return count;
}