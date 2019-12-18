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
struct ttm_buffer_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttm_bo_wait (struct ttm_buffer_object*,int,int) ; 
 int /*<<< orphan*/  vmw_bo_swap_notify (struct ttm_buffer_object*) ; 

__attribute__((used)) static void vmw_swap_notify(struct ttm_buffer_object *bo)
{
	vmw_bo_swap_notify(bo);
	(void) ttm_bo_wait(bo, false, false);
}