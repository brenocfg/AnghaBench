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
struct vmw_legacy_display_unit {int /*<<< orphan*/  base; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vmw_legacy_display_unit*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_du_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmw_ldu_destroy(struct vmw_legacy_display_unit *ldu)
{
	list_del_init(&ldu->active);
	vmw_du_cleanup(&ldu->base);
	kfree(ldu);
}