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
struct onenand_chip {int erase_shift; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLEXONENAND (struct onenand_chip*) ; 
 int flexonenand_block (struct onenand_chip*,int) ; 

inline unsigned onenand_block(struct onenand_chip *this, loff_t addr)
{
	if (!FLEXONENAND(this))
		return addr >> this->erase_shift;
	return flexonenand_block(this, addr);
}