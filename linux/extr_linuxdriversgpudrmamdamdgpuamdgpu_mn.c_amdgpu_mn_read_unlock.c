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
struct amdgpu_mn {int /*<<< orphan*/  lock; int /*<<< orphan*/  recursion; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read_non_owner (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdgpu_mn_read_unlock(struct amdgpu_mn *amn)
{
	if (atomic_dec_return(&amn->recursion) == 0)
		up_read_non_owner(&amn->lock);
}