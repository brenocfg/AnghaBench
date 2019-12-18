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
struct ib_device {int dummy; } ;
struct ib_cm_id {scalar_t__ cm_handler; scalar_t__ context; } ;
struct cm_id_private {struct ib_cm_id id; int /*<<< orphan*/  listen_sharecount; int /*<<< orphan*/  refcount; } ;
typedef  scalar_t__ ib_cm_handler ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ib_cm_id* ERR_PTR (int) ; 
 int /*<<< orphan*/  IB_CM_ASSIGN_SERVICE_ID ; 
 scalar_t__ IS_ERR (struct ib_cm_id*) ; 
 int __ib_cm_listen (struct ib_cm_id*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__ cm ; 
 struct cm_id_private* cm_find_listen (struct ib_device*,int /*<<< orphan*/ ) ; 
 struct ib_cm_id* ib_create_cm_id (struct ib_device*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_destroy_cm_id (struct ib_cm_id*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct ib_cm_id *ib_cm_insert_listen(struct ib_device *device,
				     ib_cm_handler cm_handler,
				     __be64 service_id)
{
	struct cm_id_private *cm_id_priv;
	struct ib_cm_id *cm_id;
	unsigned long flags;
	int err = 0;

	/* Create an ID in advance, since the creation may sleep */
	cm_id = ib_create_cm_id(device, cm_handler, NULL);
	if (IS_ERR(cm_id))
		return cm_id;

	spin_lock_irqsave(&cm.lock, flags);

	if (service_id == IB_CM_ASSIGN_SERVICE_ID)
		goto new_id;

	/* Find an existing ID */
	cm_id_priv = cm_find_listen(device, service_id);
	if (cm_id_priv) {
		if (cm_id->cm_handler != cm_handler || cm_id->context) {
			/* Sharing an ib_cm_id with different handlers is not
			 * supported */
			spin_unlock_irqrestore(&cm.lock, flags);
			return ERR_PTR(-EINVAL);
		}
		atomic_inc(&cm_id_priv->refcount);
		++cm_id_priv->listen_sharecount;
		spin_unlock_irqrestore(&cm.lock, flags);

		ib_destroy_cm_id(cm_id);
		cm_id = &cm_id_priv->id;
		return cm_id;
	}

new_id:
	/* Use newly created ID */
	err = __ib_cm_listen(cm_id, service_id, 0);

	spin_unlock_irqrestore(&cm.lock, flags);

	if (err) {
		ib_destroy_cm_id(cm_id);
		return ERR_PTR(err);
	}
	return cm_id;
}