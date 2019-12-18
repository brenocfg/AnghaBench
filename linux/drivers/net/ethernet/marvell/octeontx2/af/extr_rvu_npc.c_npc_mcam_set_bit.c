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
struct npc_mcam {int /*<<< orphan*/  bmap_fcnt; int /*<<< orphan*/  bmap_reverse; int /*<<< orphan*/  bmap; scalar_t__ bmap_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void npc_mcam_set_bit(struct npc_mcam *mcam, u16 index)
{
	u16 entry, rentry;

	entry = index;
	rentry = mcam->bmap_entries - index - 1;

	__set_bit(entry, mcam->bmap);
	__set_bit(rentry, mcam->bmap_reverse);
	mcam->bmap_fcnt--;
}