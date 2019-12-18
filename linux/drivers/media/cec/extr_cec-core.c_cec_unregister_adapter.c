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
struct cec_adapter {scalar_t__ notifier; int /*<<< orphan*/  cec_dir; int /*<<< orphan*/ * rc; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct cec_adapter*) ; 
 int /*<<< orphan*/  cec_devnode_unregister (struct cec_adapter*) ; 
 int /*<<< orphan*/  cec_notifier_unregister (scalar_t__) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_unregister_device (int /*<<< orphan*/ *) ; 

void cec_unregister_adapter(struct cec_adapter *adap)
{
	if (IS_ERR_OR_NULL(adap))
		return;

#ifdef CONFIG_MEDIA_CEC_RC
	/* Note: rc_unregister also calls rc_free */
	rc_unregister_device(adap->rc);
	adap->rc = NULL;
#endif
	debugfs_remove_recursive(adap->cec_dir);
#ifdef CONFIG_CEC_NOTIFIER
	if (adap->notifier)
		cec_notifier_unregister(adap->notifier);
#endif
	cec_devnode_unregister(adap);
}