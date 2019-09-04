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
struct st_clk_quadfs_fsynth {size_t chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKGEN_WRITE (struct st_clk_quadfs_fsynth*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * en ; 

__attribute__((used)) static void quadfs_fsynth_program_enable(struct st_clk_quadfs_fsynth *fs)
{
	/*
	 * Pulse the program enable register lsb to make the hardware take
	 * notice of the new md/pe values with a glitchless transition.
	 */
	CLKGEN_WRITE(fs, en[fs->chan], 1);
	CLKGEN_WRITE(fs, en[fs->chan], 0);
}