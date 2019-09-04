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
struct nvm_tgt_type {int dummy; } ;

/* Variables and functions */
 struct nvm_tgt_type* __nvm_find_target_type (char const*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvm_tgtt_lock ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nvm_tgt_type *nvm_find_target_type(const char *name)
{
	struct nvm_tgt_type *tt;

	down_write(&nvm_tgtt_lock);
	tt = __nvm_find_target_type(name);
	up_write(&nvm_tgtt_lock);

	return tt;
}