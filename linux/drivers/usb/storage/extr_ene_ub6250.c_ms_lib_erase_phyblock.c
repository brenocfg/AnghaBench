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
typedef  size_t u16 ;
struct us_data {scalar_t__ extra; } ;
struct TYPE_2__ {size_t NumberOfPhyBlock; size_t* Phy2LogMap; size_t NumberOfLogBlock; void** Log2PhyMap; } ;
struct ene_ub6250_info {TYPE_1__ MS_Lib; } ;

/* Variables and functions */
#define  MS_ERROR_FLASH_ERASE 131 
 void* MS_LB_NOT_USED ; 
 size_t MS_LB_NOT_USED_ERASED ; 
 int /*<<< orphan*/  MS_LIB_CTRL_RDONLY ; 
#define  MS_STATUS_ERROR 130 
#define  MS_STATUS_INT_ERROR 129 
#define  MS_STATUS_SUCCESS 128 
 int /*<<< orphan*/  ms_lib_ctrl_set (struct ene_ub6250_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ms_lib_error_phyblock (struct us_data*,size_t) ; 
 scalar_t__ ms_lib_iswritable (struct ene_ub6250_info*) ; 
 int /*<<< orphan*/  ms_lib_setacquired_errorblock (struct us_data*,size_t) ; 
 int ms_read_eraseblock (struct us_data*,size_t) ; 

__attribute__((used)) static int ms_lib_erase_phyblock(struct us_data *us, u16 phyblk)
{
	u16 log;
	struct ene_ub6250_info *info = (struct ene_ub6250_info *) us->extra;

	if (phyblk >= info->MS_Lib.NumberOfPhyBlock)
		return MS_STATUS_ERROR;

	log = info->MS_Lib.Phy2LogMap[phyblk];

	if (log < info->MS_Lib.NumberOfLogBlock)
		info->MS_Lib.Log2PhyMap[log] = MS_LB_NOT_USED;

	info->MS_Lib.Phy2LogMap[phyblk] = MS_LB_NOT_USED;

	if (ms_lib_iswritable(info)) {
		switch (ms_read_eraseblock(us, phyblk)) {
		case MS_STATUS_SUCCESS:
			info->MS_Lib.Phy2LogMap[phyblk] = MS_LB_NOT_USED_ERASED;
			return MS_STATUS_SUCCESS;
		case MS_ERROR_FLASH_ERASE:
		case MS_STATUS_INT_ERROR:
			ms_lib_error_phyblock(us, phyblk);
			return MS_ERROR_FLASH_ERASE;
		case MS_STATUS_ERROR:
		default:
			ms_lib_ctrl_set(info, MS_LIB_CTRL_RDONLY); /* MS_LibCtrlSet will used by ENE_MSInit ,need check, and why us to info*/
			ms_lib_setacquired_errorblock(us, phyblk);
			return MS_STATUS_ERROR;
		}
	}

	ms_lib_setacquired_errorblock(us, phyblk);

	return MS_STATUS_SUCCESS;
}