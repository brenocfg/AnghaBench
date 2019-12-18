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
struct ts_common_info {scalar_t__ TClasNum; scalar_t__ TClasProc; int /*<<< orphan*/  TClass; int /*<<< orphan*/  TSpec; int /*<<< orphan*/  Addr; } ;

/* Variables and functions */
 int TCLAS_NUM ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ResetTsCommonInfo(struct ts_common_info *pTsCommonInfo)
{
	eth_zero_addr(pTsCommonInfo->Addr);
	memset(&pTsCommonInfo->TSpec, 0, sizeof(union tspec_body));
	memset(&pTsCommonInfo->TClass, 0, sizeof(union qos_tclas)*TCLAS_NUM);
	pTsCommonInfo->TClasProc = 0;
	pTsCommonInfo->TClasNum = 0;
}