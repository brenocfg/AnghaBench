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
struct cec_adapter {int /*<<< orphan*/  rc; TYPE_1__* ops; scalar_t__ kthread_config; scalar_t__ kthread; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* adap_free ) (struct cec_adapter*) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct cec_adapter*) ; 
 int /*<<< orphan*/  kfree (struct cec_adapter*) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  rc_free_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cec_adapter*) ; 

void cec_delete_adapter(struct cec_adapter *adap)
{
	if (IS_ERR_OR_NULL(adap))
		return;
	kthread_stop(adap->kthread);
	if (adap->kthread_config)
		kthread_stop(adap->kthread_config);
	if (adap->ops->adap_free)
		adap->ops->adap_free(adap);
#ifdef CONFIG_MEDIA_CEC_RC
	rc_free_device(adap->rc);
#endif
	kfree(adap);
}