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
struct nvm_tgt_type {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvm_tgtt_lock ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void nvm_unregister_tgt_type(struct nvm_tgt_type *tt)
{
	if (!tt)
		return;

	down_write(&nvm_tgtt_lock);
	list_del(&tt->list);
	up_write(&nvm_tgtt_lock);
}