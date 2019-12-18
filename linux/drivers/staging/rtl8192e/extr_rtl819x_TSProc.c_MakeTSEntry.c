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
typedef  union tspec_body {int dummy; } tspec_body ;
typedef  union qos_tclas {int dummy; } qos_tclas ;
typedef  size_t u8 ;
struct ts_common_info {size_t* Addr; size_t TClasProc; size_t TClasNum; int /*<<< orphan*/ * TClass; int /*<<< orphan*/  TSpec; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (size_t*,size_t*,int) ; 

__attribute__((used)) static void MakeTSEntry(struct ts_common_info *pTsCommonInfo, u8 *Addr,
			union tspec_body *pTSPEC, union qos_tclas *pTCLAS,
			u8 TCLAS_Num, u8 TCLAS_Proc)
{
	u8	count;

	if (pTsCommonInfo == NULL)
		return;

	memcpy(pTsCommonInfo->Addr, Addr, 6);

	if (pTSPEC != NULL)
		memcpy((u8 *)(&(pTsCommonInfo->TSpec)), (u8 *)pTSPEC,
			sizeof(union tspec_body));

	for (count = 0; count < TCLAS_Num; count++)
		memcpy((u8 *)(&(pTsCommonInfo->TClass[count])),
		       (u8 *)pTCLAS, sizeof(union qos_tclas));

	pTsCommonInfo->TClasProc = TCLAS_Proc;
	pTsCommonInfo->TClasNum = TCLAS_Num;
}