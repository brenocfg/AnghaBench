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
 int /*<<< orphan*/  EMULATION_PREVENTION_THREE_BYTE ; 
 int /*<<< orphan*/  rbsp_write_bits (struct rbsp*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_emulation_prevention_three_byte(struct rbsp *rbsp)
{
	rbsp->num_consecutive_zeros = 0;
	rbsp_write_bits(rbsp, 8, EMULATION_PREVENTION_THREE_BYTE);

	return 0;
}