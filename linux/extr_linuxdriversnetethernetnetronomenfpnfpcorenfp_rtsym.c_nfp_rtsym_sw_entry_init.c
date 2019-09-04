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
typedef  int u64 ;
typedef  int u32 ;
struct nfp_rtsym_table {scalar_t__ strtab; } ;
struct nfp_rtsym_entry {int target; int menum; int island; int /*<<< orphan*/  size_lo; scalar_t__ size_hi; int /*<<< orphan*/  addr_lo; scalar_t__ addr_hi; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
struct nfp_rtsym {int addr; int size; int target; int domain; scalar_t__ name; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int NFP_RTSYM_TARGET_EMU_CACHE ; 
 int NFP_RTSYM_TARGET_LMEM ; 
#define  SYM_TGT_EMU_CACHE 129 
#define  SYM_TGT_LMEM 128 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int nfp_meid (int,int) ; 

__attribute__((used)) static void
nfp_rtsym_sw_entry_init(struct nfp_rtsym_table *cache, u32 strtab_size,
			struct nfp_rtsym *sw, struct nfp_rtsym_entry *fw)
{
	sw->type = fw->type;
	sw->name = cache->strtab + le16_to_cpu(fw->name) % strtab_size;
	sw->addr = ((u64)fw->addr_hi << 32) | le32_to_cpu(fw->addr_lo);
	sw->size = ((u64)fw->size_hi << 32) | le32_to_cpu(fw->size_lo);

	switch (fw->target) {
	case SYM_TGT_LMEM:
		sw->target = NFP_RTSYM_TARGET_LMEM;
		break;
	case SYM_TGT_EMU_CACHE:
		sw->target = NFP_RTSYM_TARGET_EMU_CACHE;
		break;
	default:
		sw->target = fw->target;
		break;
	}

	if (fw->menum != 0xff)
		sw->domain = nfp_meid(fw->island, fw->menum);
	else if (fw->island != 0xff)
		sw->domain = fw->island;
	else
		sw->domain = -1;
}