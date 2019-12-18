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
struct tspec_body {int dummy; } ;
struct ts_common_info {scalar_t__ t_clas_num; scalar_t__ t_clas_proc; int /*<<< orphan*/  t_class; int /*<<< orphan*/  t_spec; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int TCLAS_NUM ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ResetTsCommonInfo(struct ts_common_info *pTsCommonInfo)
{
	eth_zero_addr(pTsCommonInfo->addr);
	memset(&pTsCommonInfo->t_spec, 0, sizeof(struct tspec_body));
	memset(&pTsCommonInfo->t_class, 0, sizeof(union qos_tclas) * TCLAS_NUM);
	pTsCommonInfo->t_clas_proc = 0;
	pTsCommonInfo->t_clas_num = 0;
}