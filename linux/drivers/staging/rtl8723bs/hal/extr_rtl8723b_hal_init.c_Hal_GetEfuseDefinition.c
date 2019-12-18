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
typedef  int u8 ;
typedef  int u16 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int EFUSE_BT_MAP_LEN ; 
 int EFUSE_BT_MAX_SECTION ; 
 int EFUSE_BT_REAL_BANK_CONTENT_LEN ; 
 int EFUSE_BT_REAL_CONTENT_LEN ; 
 int EFUSE_MAX_MAP_LEN ; 
 int EFUSE_MAX_SECTION_8723B ; 
 void* EFUSE_OOB_PROTECT_BYTES ; 
 int EFUSE_PROTECT_BYTES_BANK ; 
 void* EFUSE_REAL_CONTENT_LEN_8723B ; 
 int EFUSE_WIFI ; 
#define  TYPE_AVAILABLE_EFUSE_BYTES_BANK 134 
#define  TYPE_AVAILABLE_EFUSE_BYTES_TOTAL 133 
#define  TYPE_EFUSE_CONTENT_LEN_BANK 132 
#define  TYPE_EFUSE_MAP_LEN 131 
#define  TYPE_EFUSE_MAX_SECTION 130 
#define  TYPE_EFUSE_PROTECT_BYTES_BANK 129 
#define  TYPE_EFUSE_REAL_CONTENT_LEN 128 

__attribute__((used)) static void Hal_GetEfuseDefinition(
	struct adapter *padapter,
	u8 efuseType,
	u8 type,
	void *pOut,
	bool bPseudoTest
)
{
	switch (type) {
	case TYPE_EFUSE_MAX_SECTION:
		{
			u8 *pMax_section;
			pMax_section = pOut;

			if (efuseType == EFUSE_WIFI)
				*pMax_section = EFUSE_MAX_SECTION_8723B;
			else
				*pMax_section = EFUSE_BT_MAX_SECTION;
		}
		break;

	case TYPE_EFUSE_REAL_CONTENT_LEN:
		{
			u16 *pu2Tmp;
			pu2Tmp = pOut;

			if (efuseType == EFUSE_WIFI)
				*pu2Tmp = EFUSE_REAL_CONTENT_LEN_8723B;
			else
				*pu2Tmp = EFUSE_BT_REAL_CONTENT_LEN;
		}
		break;

	case TYPE_AVAILABLE_EFUSE_BYTES_BANK:
		{
			u16 *pu2Tmp;
			pu2Tmp = pOut;

			if (efuseType == EFUSE_WIFI)
				*pu2Tmp = (EFUSE_REAL_CONTENT_LEN_8723B-EFUSE_OOB_PROTECT_BYTES);
			else
				*pu2Tmp = (EFUSE_BT_REAL_BANK_CONTENT_LEN-EFUSE_PROTECT_BYTES_BANK);
		}
		break;

	case TYPE_AVAILABLE_EFUSE_BYTES_TOTAL:
		{
			u16 *pu2Tmp;
			pu2Tmp = pOut;

			if (efuseType == EFUSE_WIFI)
				*pu2Tmp = (EFUSE_REAL_CONTENT_LEN_8723B-EFUSE_OOB_PROTECT_BYTES);
			else
				*pu2Tmp = (EFUSE_BT_REAL_CONTENT_LEN-(EFUSE_PROTECT_BYTES_BANK*3));
		}
		break;

	case TYPE_EFUSE_MAP_LEN:
		{
			u16 *pu2Tmp;
			pu2Tmp = pOut;

			if (efuseType == EFUSE_WIFI)
				*pu2Tmp = EFUSE_MAX_MAP_LEN;
			else
				*pu2Tmp = EFUSE_BT_MAP_LEN;
		}
		break;

	case TYPE_EFUSE_PROTECT_BYTES_BANK:
		{
			u8 *pu1Tmp;
			pu1Tmp = pOut;

			if (efuseType == EFUSE_WIFI)
				*pu1Tmp = EFUSE_OOB_PROTECT_BYTES;
			else
				*pu1Tmp = EFUSE_PROTECT_BYTES_BANK;
		}
		break;

	case TYPE_EFUSE_CONTENT_LEN_BANK:
		{
			u16 *pu2Tmp;
			pu2Tmp = pOut;

			if (efuseType == EFUSE_WIFI)
				*pu2Tmp = EFUSE_REAL_CONTENT_LEN_8723B;
			else
				*pu2Tmp = EFUSE_BT_REAL_BANK_CONTENT_LEN;
		}
		break;

	default:
		{
			u8 *pu1Tmp;
			pu1Tmp = pOut;
			*pu1Tmp = 0;
		}
		break;
	}
}