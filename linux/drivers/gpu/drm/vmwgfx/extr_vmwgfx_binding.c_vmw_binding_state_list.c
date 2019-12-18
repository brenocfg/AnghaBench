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
struct list_head {int dummy; } ;
struct vmw_ctx_binding_state {struct list_head list; } ;

/* Variables and functions */

struct list_head *vmw_binding_state_list(struct vmw_ctx_binding_state *cbs)
{
	return &cbs->list;
}