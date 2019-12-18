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
struct airq_iv {unsigned long bits; unsigned long end; int /*<<< orphan*/  lock; int /*<<< orphan*/  avail; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit_inv (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long find_first_bit_inv (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long find_next_bit_inv (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit_inv (unsigned long,int /*<<< orphan*/ ) ; 

unsigned long airq_iv_alloc(struct airq_iv *iv, unsigned long num)
{
	unsigned long bit, i, flags;

	if (!iv->avail || num == 0)
		return -1UL;
	spin_lock_irqsave(&iv->lock, flags);
	bit = find_first_bit_inv(iv->avail, iv->bits);
	while (bit + num <= iv->bits) {
		for (i = 1; i < num; i++)
			if (!test_bit_inv(bit + i, iv->avail))
				break;
		if (i >= num) {
			/* Found a suitable block of irqs */
			for (i = 0; i < num; i++)
				clear_bit_inv(bit + i, iv->avail);
			if (bit + num >= iv->end)
				iv->end = bit + num + 1;
			break;
		}
		bit = find_next_bit_inv(iv->avail, iv->bits, bit + i + 1);
	}
	if (bit + num > iv->bits)
		bit = -1UL;
	spin_unlock_irqrestore(&iv->lock, flags);
	return bit;
}