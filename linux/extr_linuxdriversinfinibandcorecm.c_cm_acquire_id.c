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
struct cm_id_private {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 TYPE_1__ cm ; 
 struct cm_id_private* cm_get_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct cm_id_private * cm_acquire_id(__be32 local_id, __be32 remote_id)
{
	struct cm_id_private *cm_id_priv;

	spin_lock_irq(&cm.lock);
	cm_id_priv = cm_get_id(local_id, remote_id);
	spin_unlock_irq(&cm.lock);

	return cm_id_priv;
}