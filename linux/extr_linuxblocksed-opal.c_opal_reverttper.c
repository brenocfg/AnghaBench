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
struct opal_step {int /*<<< orphan*/ * member_0; struct opal_key* member_1; } ;
struct opal_key {int dummy; } ;
struct opal_dev {int /*<<< orphan*/  dev_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  clean_opal_dev (struct opal_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int next (struct opal_dev*) ; 
 int /*<<< orphan*/ * opal_discovery0 ; 
 int /*<<< orphan*/ * revert_tper ; 
 int /*<<< orphan*/  setup_opal_dev (struct opal_dev*,struct opal_step const*) ; 
 int /*<<< orphan*/ * start_SIDASP_opal_session ; 

__attribute__((used)) static int opal_reverttper(struct opal_dev *dev, struct opal_key *opal)
{
	const struct opal_step revert_steps[] = {
		{ opal_discovery0, },
		{ start_SIDASP_opal_session, opal },
		{ revert_tper, }, /* controller will terminate session */
		{ NULL, }
	};
	int ret;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev, revert_steps);
	ret = next(dev);
	mutex_unlock(&dev->dev_lock);

	/*
	 * If we successfully reverted lets clean
	 * any saved locking ranges.
	 */
	if (!ret)
		clean_opal_dev(dev);

	return ret;
}