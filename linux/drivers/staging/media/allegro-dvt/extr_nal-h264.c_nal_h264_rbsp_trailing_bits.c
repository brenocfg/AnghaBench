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
struct rbsp {scalar_t__ pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  rbsp_bit (struct rbsp*,unsigned int*) ; 
 int /*<<< orphan*/  rbsp_bits (struct rbsp*,scalar_t__,unsigned int*) ; 
 scalar_t__ round_up (scalar_t__,int) ; 

__attribute__((used)) static void nal_h264_rbsp_trailing_bits(struct rbsp *rbsp)
{
	unsigned int rbsp_stop_one_bit = 1;
	unsigned int rbsp_alignment_zero_bit = 0;

	rbsp_bit(rbsp, &rbsp_stop_one_bit);
	rbsp_bits(rbsp, round_up(rbsp->pos, 8) - rbsp->pos,
		  &rbsp_alignment_zero_bit);
}