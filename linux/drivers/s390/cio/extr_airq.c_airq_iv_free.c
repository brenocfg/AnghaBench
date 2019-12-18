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
struct airq_iv {unsigned long end; int /*<<< orphan*/  lock; int /*<<< orphan*/  avail; int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit_inv (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit_inv (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit_inv (int,int /*<<< orphan*/ ) ; 

void airq_iv_free(struct airq_iv *iv, unsigned long bit, unsigned long num)
{
	unsigned long i, flags;

	if (!iv->avail || num == 0)
		return;
	spin_lock_irqsave(&iv->lock, flags);
	for (i = 0; i < num; i++) {
		/* Clear (possibly left over) interrupt bit */
		clear_bit_inv(bit + i, iv->vector);
		/* Make the bit positions available again */
		set_bit_inv(bit + i, iv->avail);
	}
	if (bit + num >= iv->end) {
		/* Find new end of bit-field */
		while (iv->end > 0 && !test_bit_inv(iv->end - 1, iv->avail))
			iv->end--;
	}
	spin_unlock_irqrestore(&iv->lock, flags);
}