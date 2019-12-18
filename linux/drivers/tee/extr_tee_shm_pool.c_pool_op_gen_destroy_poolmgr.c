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
struct tee_shm_pool_mgr {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tee_shm_pool_mgr*) ; 

__attribute__((used)) static void pool_op_gen_destroy_poolmgr(struct tee_shm_pool_mgr *poolm)
{
	gen_pool_destroy(poolm->private_data);
	kfree(poolm);
}