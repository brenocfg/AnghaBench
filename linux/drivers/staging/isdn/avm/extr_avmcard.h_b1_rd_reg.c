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
 int /*<<< orphan*/  READ_REGISTER ; 
 unsigned int b1_get_word (unsigned int) ; 
 int /*<<< orphan*/  b1_put_byte (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b1_put_word (unsigned int,unsigned int) ; 

__attribute__((used)) static inline unsigned int b1_rd_reg(unsigned int base,
				     unsigned int reg)
{
	b1_put_byte(base, READ_REGISTER);
	b1_put_word(base, reg);
	return b1_get_word(base);

}