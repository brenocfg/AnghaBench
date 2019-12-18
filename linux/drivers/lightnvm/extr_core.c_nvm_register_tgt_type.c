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
struct nvm_tgt_type {int /*<<< orphan*/  list; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EEXIST ; 
 scalar_t__ __nvm_find_target_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvm_tgt_types ; 
 int /*<<< orphan*/  nvm_tgtt_lock ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int nvm_register_tgt_type(struct nvm_tgt_type *tt)
{
	int ret = 0;

	down_write(&nvm_tgtt_lock);
	if (__nvm_find_target_type(tt->name))
		ret = -EEXIST;
	else
		list_add(&tt->list, &nvm_tgt_types);
	up_write(&nvm_tgtt_lock);

	return ret;
}