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

/* Variables and functions */
 scalar_t__ test_bit_le (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int log_test_bit(uint32_t *bs, unsigned bit)
{
	return test_bit_le(bit, bs) ? 1 : 0;
}