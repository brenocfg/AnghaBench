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
struct cec_notifier {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  cec_notifier_release ; 
 int /*<<< orphan*/  cec_notifiers_lock ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void cec_notifier_put(struct cec_notifier *n)
{
	mutex_lock(&cec_notifiers_lock);
	kref_put(&n->kref, cec_notifier_release);
	mutex_unlock(&cec_notifiers_lock);
}