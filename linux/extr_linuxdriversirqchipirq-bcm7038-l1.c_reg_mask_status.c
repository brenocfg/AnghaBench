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
typedef  int /*<<< orphan*/  u32 ;
struct bcm7038_l1_chip {int n_words; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int reg_mask_status(struct bcm7038_l1_chip *intc,
					   unsigned int word)
{
	return (1 * intc->n_words + word) * sizeof(u32);
}