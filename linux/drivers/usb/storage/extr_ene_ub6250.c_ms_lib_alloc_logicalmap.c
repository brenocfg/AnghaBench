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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct us_data {scalar_t__ extra; } ;
struct TYPE_2__ {int NumberOfPhyBlock; int NumberOfLogBlock; void** Log2PhyMap; void** Phy2LogMap; } ;
struct ene_ub6250_info {TYPE_1__ MS_Lib; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MS_LB_NOT_USED ; 
 void* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ms_lib_free_logicalmap (struct us_data*) ; 

__attribute__((used)) static int ms_lib_alloc_logicalmap(struct us_data *us)
{
	u32  i;
	struct ene_ub6250_info *info = (struct ene_ub6250_info *) us->extra;

	info->MS_Lib.Phy2LogMap = kmalloc_array(info->MS_Lib.NumberOfPhyBlock,
						sizeof(u16),
						GFP_KERNEL);
	info->MS_Lib.Log2PhyMap = kmalloc_array(info->MS_Lib.NumberOfLogBlock,
						sizeof(u16),
						GFP_KERNEL);

	if ((info->MS_Lib.Phy2LogMap == NULL) || (info->MS_Lib.Log2PhyMap == NULL)) {
		ms_lib_free_logicalmap(us);
		return (u32)-1;
	}

	for (i = 0; i < info->MS_Lib.NumberOfPhyBlock; i++)
		info->MS_Lib.Phy2LogMap[i] = MS_LB_NOT_USED;

	for (i = 0; i < info->MS_Lib.NumberOfLogBlock; i++)
		info->MS_Lib.Log2PhyMap[i] = MS_LB_NOT_USED;

	return 0;
}