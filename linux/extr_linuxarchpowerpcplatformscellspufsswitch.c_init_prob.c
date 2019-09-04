#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mb_stat_R; int /*<<< orphan*/  spu_runcntl_RW; } ;
struct spu_state {int* spu_chnlcnt_RW; TYPE_1__ prob; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPU_RUNCNTL_STOP ; 

__attribute__((used)) static void init_prob(struct spu_state *csa)
{
	csa->spu_chnlcnt_RW[9] = 1;
	csa->spu_chnlcnt_RW[21] = 16;
	csa->spu_chnlcnt_RW[23] = 1;
	csa->spu_chnlcnt_RW[28] = 1;
	csa->spu_chnlcnt_RW[30] = 1;
	csa->prob.spu_runcntl_RW = SPU_RUNCNTL_STOP;
	csa->prob.mb_stat_R = 0x000400;
}