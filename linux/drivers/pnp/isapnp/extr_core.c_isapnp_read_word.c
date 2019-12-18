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
 unsigned short isapnp_read_byte (unsigned char) ; 

__attribute__((used)) static unsigned short isapnp_read_word(unsigned char idx)
{
	unsigned short val;

	val = isapnp_read_byte(idx);
	val = (val << 8) + isapnp_read_byte(idx + 1);
	return val;
}