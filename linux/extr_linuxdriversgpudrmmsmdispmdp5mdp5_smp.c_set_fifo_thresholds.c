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
typedef  int u32 ;
struct mdp5_smp {int blk_size; int* pipe_reqprio_fifo_wm0; int* pipe_reqprio_fifo_wm1; int* pipe_reqprio_fifo_wm2; } ;
typedef  enum mdp5_pipe { ____Placeholder_mdp5_pipe } mdp5_pipe ;

/* Variables and functions */
 int BITS_PER_BYTE ; 

__attribute__((used)) static void set_fifo_thresholds(struct mdp5_smp *smp,
		enum mdp5_pipe pipe, int nblks)
{
	u32 smp_entries_per_blk = smp->blk_size / (128 / BITS_PER_BYTE);
	u32 val;

	/* 1/4 of SMP pool that is being fetched */
	val = (nblks * smp_entries_per_blk) / 4;

	smp->pipe_reqprio_fifo_wm0[pipe] = val * 1;
	smp->pipe_reqprio_fifo_wm1[pipe] = val * 2;
	smp->pipe_reqprio_fifo_wm2[pipe] = val * 3;
}