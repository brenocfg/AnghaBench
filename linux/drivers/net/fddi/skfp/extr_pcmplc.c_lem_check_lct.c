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
struct TYPE_2__ {scalar_t__ lct_extended; scalar_t__ lct_long; scalar_t__ lct_medium; scalar_t__ lct_short; } ;
struct s_smc {TYPE_1__ s; } ;
struct lem_counter {scalar_t__ lem_errors; } ;
struct s_phy {int lc_test; void* pc_lem_fail; scalar_t__ np; struct fddi_mib_p* mib; struct lem_counter lem; } ;
struct fddi_mib_p {int fddiPORTLem_Ct; scalar_t__ fddiPORTLCTFail_Ct; int /*<<< orphan*/  fddiPORTLem_Reject_Ct; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_PCMN (int,char*,scalar_t__) ; 
 void* FALSE ; 
#define  LC_EXTENDED 131 
#define  LC_LONG 130 
#define  LC_MEDIUM 129 
#define  LC_SHORT 128 
 int /*<<< orphan*/  PLC (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PL_LINK_ERR_CTR ; 
 void* TRUE ; 
 int inpw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lem_check_lct(struct s_smc *smc, struct s_phy *phy)
{
	struct lem_counter	*lem = &phy->lem ;
	struct fddi_mib_p	*mib ;
	int errors ;

	mib = phy->mib ;

	phy->pc_lem_fail = FALSE ;		/* flag */
	errors = inpw(PLC(((int)phy->np),PL_LINK_ERR_CTR)) ;
	lem->lem_errors += errors ;
	mib->fddiPORTLem_Ct += errors ;
	if (lem->lem_errors) {
		switch(phy->lc_test) {
		case LC_SHORT:
			if (lem->lem_errors >= smc->s.lct_short)
				phy->pc_lem_fail = TRUE ;
			break ;
		case LC_MEDIUM:
			if (lem->lem_errors >= smc->s.lct_medium)
				phy->pc_lem_fail = TRUE ;
			break ;
		case LC_LONG:
			if (lem->lem_errors >= smc->s.lct_long)
				phy->pc_lem_fail = TRUE ;
			break ;
		case LC_EXTENDED:
			if (lem->lem_errors >= smc->s.lct_extended)
				phy->pc_lem_fail = TRUE ;
			break ;
		}
		DB_PCMN(1, " >>errors : %lu", lem->lem_errors);
	}
	if (phy->pc_lem_fail) {
		mib->fddiPORTLCTFail_Ct++ ;
		mib->fddiPORTLem_Reject_Ct++ ;
	}
	else
		mib->fddiPORTLCTFail_Ct = 0 ;
}