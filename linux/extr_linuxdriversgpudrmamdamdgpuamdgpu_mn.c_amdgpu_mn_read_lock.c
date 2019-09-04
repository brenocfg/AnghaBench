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
struct amdgpu_mn {int /*<<< orphan*/  read_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  recursion; } ;

/* Variables and functions */
 int EAGAIN ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read_non_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_mn_read_lock(struct amdgpu_mn *amn, bool blockable)
{
	if (blockable)
		mutex_lock(&amn->read_lock);
	else if (!mutex_trylock(&amn->read_lock))
		return -EAGAIN;

	if (atomic_inc_return(&amn->recursion) == 1)
		down_read_non_owner(&amn->lock);
	mutex_unlock(&amn->read_lock);

	return 0;
}