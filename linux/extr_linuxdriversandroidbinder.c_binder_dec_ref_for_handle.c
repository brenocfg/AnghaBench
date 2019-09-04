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
typedef  int /*<<< orphan*/  uint32_t ;
struct binder_ref_data {int dummy; } ;
struct binder_proc {int dummy; } ;

/* Variables and functions */
 int binder_update_ref_for_handle (struct binder_proc*,int /*<<< orphan*/ ,int,int,struct binder_ref_data*) ; 

__attribute__((used)) static int binder_dec_ref_for_handle(struct binder_proc *proc,
		uint32_t desc, bool strong, struct binder_ref_data *rdata)
{
	return binder_update_ref_for_handle(proc, desc, false, strong, rdata);
}