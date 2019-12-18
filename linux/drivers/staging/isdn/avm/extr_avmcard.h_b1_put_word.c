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
 int /*<<< orphan*/  b1_put_byte (unsigned int,unsigned int) ; 

__attribute__((used)) static inline void b1_put_word(unsigned int base, unsigned int val)
{
	b1_put_byte(base, val & 0xff);
	b1_put_byte(base, (val >> 8) & 0xff);
	b1_put_byte(base, (val >> 16) & 0xff);
	b1_put_byte(base, (val >> 24) & 0xff);
}