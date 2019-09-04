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
typedef  int ulong ;

/* Variables and functions */
 int AOE_PARTITIONS ; 
 int N_DEVS ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  used_minors ; 
 int /*<<< orphan*/  used_minors_lock ; 

__attribute__((used)) static int
minor_get_dyn(ulong *sysminor)
{
	ulong flags;
	ulong n;
	int error = 0;

	spin_lock_irqsave(&used_minors_lock, flags);
	n = find_first_zero_bit(used_minors, N_DEVS);
	if (n < N_DEVS)
		set_bit(n, used_minors);
	else
		error = -1;
	spin_unlock_irqrestore(&used_minors_lock, flags);

	*sysminor = n * AOE_PARTITIONS;
	return error;
}