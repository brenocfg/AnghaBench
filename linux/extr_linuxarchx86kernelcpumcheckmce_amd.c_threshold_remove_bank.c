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
struct threshold_bank {int /*<<< orphan*/  kobj; int /*<<< orphan*/  cpus; int /*<<< orphan*/  blocks; } ;
struct amd_northbridge {int /*<<< orphan*/ * bank4; } ;

/* Variables and functions */
 int /*<<< orphan*/  __threshold_remove_blocks (struct threshold_bank*) ; 
 int /*<<< orphan*/  amd_get_nb_id (unsigned int) ; 
 int /*<<< orphan*/  deallocate_threshold_block (unsigned int,int) ; 
 scalar_t__ is_shared_bank (int) ; 
 int /*<<< orphan*/  kfree (struct threshold_bank*) ; 
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 struct amd_northbridge* node_to_amd_nb (int /*<<< orphan*/ ) ; 
 struct threshold_bank** per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  threshold_banks ; 

__attribute__((used)) static void threshold_remove_bank(unsigned int cpu, int bank)
{
	struct amd_northbridge *nb;
	struct threshold_bank *b;

	b = per_cpu(threshold_banks, cpu)[bank];
	if (!b)
		return;

	if (!b->blocks)
		goto free_out;

	if (is_shared_bank(bank)) {
		if (!refcount_dec_and_test(&b->cpus)) {
			__threshold_remove_blocks(b);
			per_cpu(threshold_banks, cpu)[bank] = NULL;
			return;
		} else {
			/*
			 * the last CPU on this node using the shared bank is
			 * going away, remove that bank now.
			 */
			nb = node_to_amd_nb(amd_get_nb_id(cpu));
			nb->bank4 = NULL;
		}
	}

	deallocate_threshold_block(cpu, bank);

free_out:
	kobject_del(b->kobj);
	kobject_put(b->kobj);
	kfree(b);
	per_cpu(threshold_banks, cpu)[bank] = NULL;
}