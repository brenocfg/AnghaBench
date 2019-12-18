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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int max; } ;
struct npc_mcam {scalar_t__* cntr2pfvf_map; TYPE_1__ counters; } ;

/* Variables and functions */
 int NPC_MCAM_INVALID_REQ ; 
 int NPC_MCAM_PERM_DENIED ; 

__attribute__((used)) static int npc_mcam_verify_counter(struct npc_mcam *mcam,
				   u16 pcifunc, int cntr)
{
	/* Verify if counter is valid and if it is indeed
	 * allocated to the requesting PFFUNC.
	 */
	if (cntr >= mcam->counters.max)
		return NPC_MCAM_INVALID_REQ;

	if (pcifunc != mcam->cntr2pfvf_map[cntr])
		return NPC_MCAM_PERM_DENIED;

	return 0;
}