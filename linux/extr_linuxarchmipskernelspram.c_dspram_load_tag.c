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
 unsigned int CKSEG0 ; 
 int /*<<< orphan*/  ERRCTL_SPRAM ; 
 int /*<<< orphan*/  Index_Load_Tag_D ; 
 unsigned int bis_c0_errctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_op (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ehb () ; 
 unsigned int read_c0_dtaglo () ; 
 int /*<<< orphan*/  write_c0_errctl (unsigned int) ; 

__attribute__((used)) static unsigned int dspram_load_tag(unsigned int offset)
{
	unsigned int data;
	unsigned int errctl;

	errctl = bis_c0_errctl(ERRCTL_SPRAM);
	ehb();
	cache_op(Index_Load_Tag_D, CKSEG0 | offset);
	ehb();
	data = read_c0_dtaglo();
	ehb();
	write_c0_errctl(errctl);
	ehb();

	return data;
}