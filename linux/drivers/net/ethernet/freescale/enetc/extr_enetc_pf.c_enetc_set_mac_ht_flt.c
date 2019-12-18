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
typedef  int /*<<< orphan*/  u32 ;
struct enetc_si {int errata; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int ENETC_ERR_UCMCSWP ; 
 int /*<<< orphan*/  ENETC_PSIMMHFR0 (int,int) ; 
 int /*<<< orphan*/  ENETC_PSIMMHFR1 (int) ; 
 int /*<<< orphan*/  ENETC_PSIUMHFR0 (int,int) ; 
 int /*<<< orphan*/  ENETC_PSIUMHFR1 (int) ; 
 int UC ; 
 int /*<<< orphan*/  enetc_port_wr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enetc_set_mac_ht_flt(struct enetc_si *si, int si_idx, int type,
				 u32 *hash)
{
	bool err = si->errata & ENETC_ERR_UCMCSWP;

	if (type == UC) {
		enetc_port_wr(&si->hw, ENETC_PSIUMHFR0(si_idx, err), *hash);
		enetc_port_wr(&si->hw, ENETC_PSIUMHFR1(si_idx), *(hash + 1));
	} else { /* MC */
		enetc_port_wr(&si->hw, ENETC_PSIMMHFR0(si_idx, err), *hash);
		enetc_port_wr(&si->hw, ENETC_PSIMMHFR1(si_idx), *(hash + 1));
	}
}