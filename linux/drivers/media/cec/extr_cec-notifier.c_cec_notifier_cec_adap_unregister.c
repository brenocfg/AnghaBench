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
struct cec_notifier {int /*<<< orphan*/  lock; int /*<<< orphan*/ * callback; TYPE_1__* cec_adap; } ;
struct TYPE_2__ {int /*<<< orphan*/ * notifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  cec_notifier_put (struct cec_notifier*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void cec_notifier_cec_adap_unregister(struct cec_notifier *n)
{
	if (!n)
		return;

	mutex_lock(&n->lock);
	n->cec_adap->notifier = NULL;
	n->cec_adap = NULL;
	n->callback = NULL;
	mutex_unlock(&n->lock);
	cec_notifier_put(n);
}