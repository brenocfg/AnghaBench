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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  PDM_ODM_T ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int* Array_MP_8723B_PHY_REG ; 
 int BIT28 ; 
 int BIT29 ; 
 scalar_t__ COND_ELSE ; 
 scalar_t__ COND_ENDIF ; 
 int /*<<< orphan*/  CheckNegative (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CheckPositive (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ODM_COMP_INIT ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  READ_NEXT_PAIR (int,int,int) ; 
 int /*<<< orphan*/  bMaskDWord ; 
 int /*<<< orphan*/  odm_ConfigBB_PHY_8723B (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

void ODM_ReadAndConfig_MP_8723B_PHY_REG(PDM_ODM_T pDM_Odm)
{
	u32 i = 0;
	u32 ArrayLen = ARRAY_SIZE(Array_MP_8723B_PHY_REG);
	u32 *Array = Array_MP_8723B_PHY_REG;

	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_INIT,
		ODM_DBG_LOUD,
		("===> ODM_ReadAndConfig_MP_8723B_PHY_REG\n")
	);

	for (i = 0; i < ArrayLen; i += 2) {
		u32 v1 = Array[i];
		u32 v2 = Array[i+1];

		/*  This (offset, data) pair doesn't care the condition. */
		if (v1 < 0x40000000) {
			odm_ConfigBB_PHY_8723B(pDM_Odm, v1, bMaskDWord, v2);
			continue;
		} else {
			/*  This line is the beginning of branch. */
			bool bMatched = true;
			u8  cCond  = (u8)((v1 & (BIT29|BIT28)) >> 28);

			if (cCond == COND_ELSE) { /*  ELSE, ENDIF */
				bMatched = true;
				READ_NEXT_PAIR(v1, v2, i);
			} else if (!CheckPositive(pDM_Odm, v1, v2)) {
				bMatched = false;
				READ_NEXT_PAIR(v1, v2, i);
				READ_NEXT_PAIR(v1, v2, i);
			} else {
				READ_NEXT_PAIR(v1, v2, i);
				if (!CheckNegative(pDM_Odm, v1, v2))
					bMatched = false;
				else
					bMatched = true;
				READ_NEXT_PAIR(v1, v2, i);
			}

			if (!bMatched) {
				/*  Condition isn't matched.
				*   Discard the following (offset, data) pairs.
				*/
				while (v1 < 0x40000000 && i < ArrayLen-2)
					READ_NEXT_PAIR(v1, v2, i);

				i -= 2; /*  prevent from for-loop += 2 */
			} else { /*  Configure matched pairs and skip to end of if-else. */
				while (v1 < 0x40000000 && i < ArrayLen-2) {
					odm_ConfigBB_PHY_8723B(pDM_Odm, v1, bMaskDWord, v2);
					READ_NEXT_PAIR(v1, v2, i);
				}

				/*  Keeps reading until ENDIF. */
				cCond = (u8)((v1 & (BIT29|BIT28)) >> 28);
				while (cCond != COND_ENDIF && i < ArrayLen-2) {
					READ_NEXT_PAIR(v1, v2, i);
					cCond = (u8)((v1 & (BIT29|BIT28)) >> 28);
				}
			}
		}
	}
}