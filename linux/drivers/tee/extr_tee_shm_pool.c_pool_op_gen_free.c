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
struct tee_shm {int /*<<< orphan*/ * kaddr; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pool_op_gen_free(struct tee_shm_pool_mgr *poolm,
			     struct tee_shm *shm)
{
	gen_pool_free(poolm->private_data, (unsigned long)shm->kaddr,
		      shm->size);
	shm->kaddr = NULL;
}