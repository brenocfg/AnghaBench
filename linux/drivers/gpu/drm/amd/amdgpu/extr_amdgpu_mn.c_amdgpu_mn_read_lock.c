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
struct amdgpu_mn {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read_trylock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_mn_read_lock(struct amdgpu_mn *amn, bool blockable)
{
	if (blockable)
		down_read(&amn->lock);
	else if (!down_read_trylock(&amn->lock))
		return -EAGAIN;

	return 0;
}