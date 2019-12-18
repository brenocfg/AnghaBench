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
struct npc_mcam {int banksize; scalar_t__ keysize; } ;

/* Variables and functions */
 scalar_t__ NPC_MCAM_KEY_X2 ; 

__attribute__((used)) static int npc_get_bank(struct npc_mcam *mcam, int index)
{
	int bank = index / mcam->banksize;

	/* 0,1 & 2,3 banks are combined for this keysize */
	if (mcam->keysize == NPC_MCAM_KEY_X2)
		return bank ? 2 : 0;

	return bank;
}