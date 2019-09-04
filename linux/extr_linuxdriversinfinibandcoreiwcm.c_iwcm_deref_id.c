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
struct iwcm_id_private {int /*<<< orphan*/  work_list; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_cm_id (struct iwcm_id_private*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwcm_deref_id(struct iwcm_id_private *cm_id_priv)
{
	BUG_ON(atomic_read(&cm_id_priv->refcount)==0);
	if (atomic_dec_and_test(&cm_id_priv->refcount)) {
		BUG_ON(!list_empty(&cm_id_priv->work_list));
		free_cm_id(cm_id_priv);
		return 1;
	}

	return 0;
}