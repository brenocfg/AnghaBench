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
struct rbsp {int pos; int size; int* buf; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static inline int rbsp_read_bit(struct rbsp *rbsp)
{
	int shift = 7 - (rbsp->pos % 8);
	int ofs = rbsp->pos++ / 8;

	if (ofs >= rbsp->size)
		return -EINVAL;

	return (rbsp->buf[ofs] >> shift) & 1;
}