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
struct rbsp {int num_consecutive_zeros; int pos; int size; int* data; } ;

/* Variables and functions */
 int EINVAL ; 
 int discard_emulation_prevention_three_byte (struct rbsp*) ; 

__attribute__((used)) static inline int rbsp_read_bit(struct rbsp *rbsp)
{
	int shift;
	int ofs;
	int bit;
	int err;

	if (rbsp->num_consecutive_zeros == 22) {
		err = discard_emulation_prevention_three_byte(rbsp);
		if (err)
			return err;
	}

	shift = 7 - (rbsp->pos % 8);
	ofs = rbsp->pos / 8;
	if (ofs >= rbsp->size)
		return -EINVAL;

	bit = (rbsp->data[ofs] >> shift) & 1;

	rbsp->pos++;

	if (bit == 1 ||
	    (rbsp->num_consecutive_zeros < 7 && (rbsp->pos % 8 == 0)))
		rbsp->num_consecutive_zeros = 0;
	else
		rbsp->num_consecutive_zeros++;

	return bit;
}