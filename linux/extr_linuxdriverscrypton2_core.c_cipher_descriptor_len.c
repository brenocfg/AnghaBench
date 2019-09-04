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

__attribute__((used)) static inline int cipher_descriptor_len(int nbytes, unsigned int block_size)
{
	int this_len = nbytes;

	this_len -= (nbytes & (block_size - 1));
	return this_len > (1 << 16) ? (1 << 16) : this_len;
}