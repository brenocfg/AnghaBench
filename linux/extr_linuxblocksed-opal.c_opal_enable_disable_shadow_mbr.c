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
struct opal_step {scalar_t__* member_1; int /*<<< orphan*/ * member_0; } ;
struct opal_mbr_data {scalar_t__ key; scalar_t__ enable_disable; } ;
struct opal_dev {int /*<<< orphan*/  dev_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ OPAL_MBR_DISABLE ; 
 scalar_t__ OPAL_MBR_ENABLE ; 
 int /*<<< orphan*/ * end_opal_session ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int next (struct opal_dev*) ; 
 int /*<<< orphan*/ * opal_discovery0 ; 
 int /*<<< orphan*/ * set_mbr_done ; 
 int /*<<< orphan*/ * set_mbr_enable_disable ; 
 int /*<<< orphan*/  setup_opal_dev (struct opal_dev*,struct opal_step const*) ; 
 int /*<<< orphan*/ * start_admin1LSP_opal_session ; 

__attribute__((used)) static int opal_enable_disable_shadow_mbr(struct opal_dev *dev,
					  struct opal_mbr_data *opal_mbr)
{
	const struct opal_step mbr_steps[] = {
		{ opal_discovery0, },
		{ start_admin1LSP_opal_session, &opal_mbr->key },
		{ set_mbr_done, &opal_mbr->enable_disable },
		{ end_opal_session, },
		{ start_admin1LSP_opal_session, &opal_mbr->key },
		{ set_mbr_enable_disable, &opal_mbr->enable_disable },
		{ end_opal_session, },
		{ NULL, }
	};
	int ret;

	if (opal_mbr->enable_disable != OPAL_MBR_ENABLE &&
	    opal_mbr->enable_disable != OPAL_MBR_DISABLE)
		return -EINVAL;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev, mbr_steps);
	ret = next(dev);
	mutex_unlock(&dev->dev_lock);
	return ret;
}