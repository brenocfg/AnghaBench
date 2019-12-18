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
struct tee_shm {int dummy; } ;
struct tee_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEE_SHM_MAPPED ; 
 struct tee_shm* __tee_shm_alloc (int /*<<< orphan*/ *,struct tee_device*,size_t,int /*<<< orphan*/ ) ; 

struct tee_shm *tee_shm_priv_alloc(struct tee_device *teedev, size_t size)
{
	return __tee_shm_alloc(NULL, teedev, size, TEE_SHM_MAPPED);
}