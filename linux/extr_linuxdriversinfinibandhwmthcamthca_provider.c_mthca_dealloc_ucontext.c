#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ib_ucontext {int /*<<< orphan*/  device; } ;
struct TYPE_3__ {int /*<<< orphan*/  uar; int /*<<< orphan*/  db_tab; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  mthca_cleanup_user_db_tab (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_uar_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_mdev (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_mucontext (struct ib_ucontext*) ; 

__attribute__((used)) static int mthca_dealloc_ucontext(struct ib_ucontext *context)
{
	mthca_cleanup_user_db_tab(to_mdev(context->device), &to_mucontext(context)->uar,
				  to_mucontext(context)->db_tab);
	mthca_uar_free(to_mdev(context->device), &to_mucontext(context)->uar);
	kfree(to_mucontext(context));

	return 0;
}