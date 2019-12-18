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
typedef  int /*<<< orphan*/  uint32_t ;
struct log_c {int touched_cleaned; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_bit_le (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void log_set_bit(struct log_c *l,
			       uint32_t *bs, unsigned bit)
{
	__set_bit_le(bit, bs);
	l->touched_cleaned = 1;
}