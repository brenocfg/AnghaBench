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

/* Variables and functions */
 int EBUSY ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qe_lock ; 
 int qe_num_of_snum ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snum_state ; 
 int* snums ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int qe_get_snum(void)
{
	unsigned long flags;
	int snum = -EBUSY;
	int i;

	spin_lock_irqsave(&qe_lock, flags);
	i = find_first_zero_bit(snum_state, qe_num_of_snum);
	if (i < qe_num_of_snum) {
		set_bit(i, snum_state);
		snum = snums[i];
	}
	spin_unlock_irqrestore(&qe_lock, flags);

	return snum;
}