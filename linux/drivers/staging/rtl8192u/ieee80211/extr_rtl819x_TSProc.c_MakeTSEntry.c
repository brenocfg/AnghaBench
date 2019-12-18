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
typedef  union qos_tclas {int dummy; } qos_tclas ;
typedef  size_t u8 ;
struct tspec_body {int dummy; } ;
struct ts_common_info {size_t* addr; size_t t_clas_proc; size_t t_clas_num; int /*<<< orphan*/ * t_class; int /*<<< orphan*/  t_spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (size_t*,size_t*,int) ; 

__attribute__((used)) static void MakeTSEntry(struct ts_common_info *pTsCommonInfo, u8 *Addr,
			struct tspec_body *pTSPEC, union qos_tclas *pTCLAS, u8 TCLAS_Num,
			u8 TCLAS_Proc)
{
	u8	count;

	if (pTsCommonInfo == NULL)
		return;

	memcpy(pTsCommonInfo->addr, Addr, 6);

	if (pTSPEC != NULL)
		memcpy((u8 *)(&(pTsCommonInfo->t_spec)), (u8 *)pTSPEC, sizeof(struct tspec_body));

	for (count = 0; count < TCLAS_Num; count++)
		memcpy((u8 *)(&(pTsCommonInfo->t_class[count])), (u8 *)pTCLAS, sizeof(union qos_tclas));

	pTsCommonInfo->t_clas_proc = TCLAS_Proc;
	pTsCommonInfo->t_clas_num = TCLAS_Num;
}