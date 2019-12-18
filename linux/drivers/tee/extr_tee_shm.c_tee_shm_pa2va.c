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
struct tee_shm {int flags; scalar_t__ paddr; scalar_t__ size; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int TEE_SHM_MAPPED ; 
 void* tee_shm_get_va (struct tee_shm*,scalar_t__) ; 

int tee_shm_pa2va(struct tee_shm *shm, phys_addr_t pa, void **va)
{
	if (!(shm->flags & TEE_SHM_MAPPED))
		return -EINVAL;
	/* Check that we're in the range of the shm */
	if (pa < shm->paddr)
		return -EINVAL;
	if (pa >= (shm->paddr + shm->size))
		return -EINVAL;

	if (va) {
		void *v = tee_shm_get_va(shm, pa - shm->paddr);

		if (IS_ERR(v))
			return PTR_ERR(v);
		*va = v;
	}
	return 0;
}