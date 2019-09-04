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
struct vmw_ctx_bindinfo {int /*<<< orphan*/ * ctx; int /*<<< orphan*/  res_list; int /*<<< orphan*/  ctx_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmw_binding_drop(struct vmw_ctx_bindinfo *bi)
{
	list_del(&bi->ctx_list);
	if (!list_empty(&bi->res_list))
		list_del(&bi->res_list);
	bi->ctx = NULL;
}