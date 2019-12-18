#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ remote_id; } ;
struct cm_id_private {int /*<<< orphan*/  refcount; TYPE_1__ id; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  local_id_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_2__ cm ; 
 int /*<<< orphan*/  cm_local_id (scalar_t__) ; 
 struct cm_id_private* xa_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cm_id_private * cm_get_id(__be32 local_id, __be32 remote_id)
{
	struct cm_id_private *cm_id_priv;

	cm_id_priv = xa_load(&cm.local_id_table, cm_local_id(local_id));
	if (cm_id_priv) {
		if (cm_id_priv->id.remote_id == remote_id)
			atomic_inc(&cm_id_priv->refcount);
		else
			cm_id_priv = NULL;
	}

	return cm_id_priv;
}