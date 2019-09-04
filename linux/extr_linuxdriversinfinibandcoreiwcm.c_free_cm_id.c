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
struct iwcm_id_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dealloc_work_entries (struct iwcm_id_private*) ; 
 int /*<<< orphan*/  kfree (struct iwcm_id_private*) ; 

__attribute__((used)) static void free_cm_id(struct iwcm_id_private *cm_id_priv)
{
	dealloc_work_entries(cm_id_priv);
	kfree(cm_id_priv);
}