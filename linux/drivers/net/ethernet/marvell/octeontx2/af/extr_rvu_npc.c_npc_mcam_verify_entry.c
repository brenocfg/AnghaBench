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
typedef  scalar_t__ u16 ;
struct npc_mcam {int bmap_entries; scalar_t__* entry2pfvf_map; } ;

/* Variables and functions */
 int NPC_MCAM_INVALID_REQ ; 
 int NPC_MCAM_PERM_DENIED ; 

__attribute__((used)) static int npc_mcam_verify_entry(struct npc_mcam *mcam,
				 u16 pcifunc, int entry)
{
	/* Verify if entry is valid and if it is indeed
	 * allocated to the requesting PFFUNC.
	 */
	if (entry >= mcam->bmap_entries)
		return NPC_MCAM_INVALID_REQ;

	if (pcifunc != mcam->entry2pfvf_map[entry])
		return NPC_MCAM_PERM_DENIED;

	return 0;
}