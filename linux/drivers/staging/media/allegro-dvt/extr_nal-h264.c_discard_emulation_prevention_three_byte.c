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
struct rbsp {scalar_t__ num_consecutive_zeros; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int EMULATION_PREVENTION_THREE_BYTE ; 
 int /*<<< orphan*/  rbsp_read_bits (struct rbsp*,int,unsigned int*) ; 

__attribute__((used)) static int discard_emulation_prevention_three_byte(struct rbsp *rbsp)
{
	unsigned int tmp = 0;

	rbsp->num_consecutive_zeros = 0;
	rbsp_read_bits(rbsp, 8, &tmp);
	if (tmp != EMULATION_PREVENTION_THREE_BYTE)
		return -EINVAL;

	return 0;
}