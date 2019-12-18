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
struct rio_pwrite {int (* pwcback ) (struct rio_mport*,void*,union rio_pw_msg*,int) ;int /*<<< orphan*/  node; void* context; } ;
struct rio_mport {int /*<<< orphan*/  lock; int /*<<< orphan*/  pwrites; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct rio_pwrite* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int rio_add_mport_pw_handler(struct rio_mport *mport, void *context,
			     int (*pwcback)(struct rio_mport *mport,
			     void *context, union rio_pw_msg *msg, int step))
{
	struct rio_pwrite *pwrite = kzalloc(sizeof(*pwrite), GFP_KERNEL);

	if (!pwrite)
		return -ENOMEM;

	pwrite->pwcback = pwcback;
	pwrite->context = context;
	mutex_lock(&mport->lock);
	list_add_tail(&pwrite->node, &mport->pwrites);
	mutex_unlock(&mport->lock);
	return 0;
}