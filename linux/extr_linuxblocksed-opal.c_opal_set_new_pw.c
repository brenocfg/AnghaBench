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
struct opal_step {int /*<<< orphan*/ * member_0; TYPE_1__* member_1; } ;
struct TYPE_2__ {scalar_t__ who; } ;
struct opal_new_pw {TYPE_1__ new_user_pw; TYPE_1__ session; } ;
struct opal_dev {int /*<<< orphan*/  dev_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ OPAL_ADMIN1 ; 
 scalar_t__ OPAL_USER9 ; 
 int /*<<< orphan*/ * end_opal_session ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int next (struct opal_dev*) ; 
 int /*<<< orphan*/ * opal_discovery0 ; 
 int /*<<< orphan*/ * set_new_pw ; 
 int /*<<< orphan*/  setup_opal_dev (struct opal_dev*,struct opal_step const*) ; 
 int /*<<< orphan*/ * start_auth_opal_session ; 

__attribute__((used)) static int opal_set_new_pw(struct opal_dev *dev, struct opal_new_pw *opal_pw)
{
	const struct opal_step pw_steps[] = {
		{ opal_discovery0, },
		{ start_auth_opal_session, &opal_pw->session },
		{ set_new_pw, &opal_pw->new_user_pw },
		{ end_opal_session, },
		{ NULL }
	};
	int ret;

	if (opal_pw->session.who < OPAL_ADMIN1 ||
	    opal_pw->session.who > OPAL_USER9  ||
	    opal_pw->new_user_pw.who < OPAL_ADMIN1 ||
	    opal_pw->new_user_pw.who > OPAL_USER9)
		return -EINVAL;

	mutex_lock(&dev->dev_lock);
	setup_opal_dev(dev, pw_steps);
	ret = next(dev);
	mutex_unlock(&dev->dev_lock);
	return ret;
}