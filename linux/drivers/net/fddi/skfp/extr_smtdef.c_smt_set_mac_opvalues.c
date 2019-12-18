#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_6__ {TYPE_2__* m; TYPE_1__* a; } ;
struct s_smc {TYPE_3__ mib; } ;
struct TYPE_5__ {int /*<<< orphan*/  fddiMACT_Req; int /*<<< orphan*/  fddiMACT_ReqMIB; int /*<<< orphan*/  fddiMACT_Max; int /*<<< orphan*/  fddiMACT_MaxMIB; int /*<<< orphan*/  fddiMACTvxValue; int /*<<< orphan*/  fddiMACTvxValueMIB; } ;
struct TYPE_4__ {int /*<<< orphan*/  fddiPATHMaxT_Req; int /*<<< orphan*/  fddiPATHT_MaxLowerBound; int /*<<< orphan*/  fddiPATHTVXLowerBound; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIX_EVENT (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FDDI_REMOTE_T_REQ ; 
 scalar_t__ FDDI_RING_STATUS ; 
 scalar_t__ FDDI_SMT_EVENT ; 
 size_t MAC0 ; 
 size_t PATH0 ; 
 int set_min_max (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smt_get_event_word (struct s_smc*) ; 

int smt_set_mac_opvalues(struct s_smc *smc)
{
	int	st ;
	int	st2 ;

	st = set_min_max(1,smc->mib.m[MAC0].fddiMACTvxValueMIB,
		smc->mib.a[PATH0].fddiPATHTVXLowerBound,
		&smc->mib.m[MAC0].fddiMACTvxValue) ;
	st |= set_min_max(0,smc->mib.m[MAC0].fddiMACT_MaxMIB,
		smc->mib.a[PATH0].fddiPATHT_MaxLowerBound,
		&smc->mib.m[MAC0].fddiMACT_Max) ;
	st |= (st2 = set_min_max(0,smc->mib.m[MAC0].fddiMACT_ReqMIB,
		smc->mib.a[PATH0].fddiPATHMaxT_Req,
		&smc->mib.m[MAC0].fddiMACT_Req)) ;
	if (st2) {
		/* Treq attribute changed remotely. So send an AIX_EVENT to the
		 * user
		 */
		AIX_EVENT(smc, (u_long) FDDI_RING_STATUS, (u_long)
			FDDI_SMT_EVENT, (u_long) FDDI_REMOTE_T_REQ,
			smt_get_event_word(smc));
	}
	return st;
}