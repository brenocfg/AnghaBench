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
struct mtd_info {int dummy; } ;
struct map_info {struct cfi_private* fldrv_priv; } ;
struct cfi_private {TYPE_1__* cfiq; } ;
typedef  int __u16 ;
struct TYPE_2__ {int P_ID; int A_ID; } ;

/* Variables and functions */
#define  P_ID_AMD_STD 134 
#define  P_ID_INTEL_EXT 133 
#define  P_ID_INTEL_PERFORMANCE 132 
#define  P_ID_INTEL_STD 131 
 int P_ID_NONE ; 
 int P_ID_RESERVED ; 
#define  P_ID_SST_OLD 130 
#define  P_ID_ST_ADV 129 
#define  P_ID_WINBOND 128 
 struct mtd_info* cfi_cmdset_0001 (struct map_info*,int) ; 
 struct mtd_info* cfi_cmdset_0002 (struct map_info*,int) ; 
 struct mtd_info* cfi_cmdset_0020 (struct map_info*,int) ; 
 struct mtd_info* cfi_cmdset_unknown (struct map_info*,int) ; 

__attribute__((used)) static struct mtd_info *check_cmd_set(struct map_info *map, int primary)
{
	struct cfi_private *cfi = map->fldrv_priv;
	__u16 type = primary?cfi->cfiq->P_ID:cfi->cfiq->A_ID;

	if (type == P_ID_NONE || type == P_ID_RESERVED)
		return NULL;

	switch(type){
		/* We need these for the !CONFIG_MODULES case,
		   because symbol_get() doesn't work there */
#ifdef CONFIG_MTD_CFI_INTELEXT
	case P_ID_INTEL_EXT:
	case P_ID_INTEL_STD:
	case P_ID_INTEL_PERFORMANCE:
		return cfi_cmdset_0001(map, primary);
#endif
#ifdef CONFIG_MTD_CFI_AMDSTD
	case P_ID_AMD_STD:
	case P_ID_SST_OLD:
	case P_ID_WINBOND:
		return cfi_cmdset_0002(map, primary);
#endif
#ifdef CONFIG_MTD_CFI_STAA
        case P_ID_ST_ADV:
		return cfi_cmdset_0020(map, primary);
#endif
	default:
		return cfi_cmdset_unknown(map, primary);
	}
}