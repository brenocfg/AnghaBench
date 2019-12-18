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
struct txdds_ent {int dummy; } ;
struct qib_pportdata {scalar_t__ link_speed_active; } ;

/* Variables and functions */
 scalar_t__ QIB_IB_DDR ; 
 scalar_t__ QIB_IB_QDR ; 
 int /*<<< orphan*/  find_best_ent (struct qib_pportdata*,struct txdds_ent const**,struct txdds_ent const**,struct txdds_ent const**,int) ; 
 int /*<<< orphan*/  write_tx_serdes_param (struct qib_pportdata*,struct txdds_ent*) ; 

__attribute__((used)) static void adj_tx_serdes(struct qib_pportdata *ppd)
{
	const struct txdds_ent *sdr_dds, *ddr_dds, *qdr_dds;
	struct txdds_ent *dds;

	find_best_ent(ppd, &sdr_dds, &ddr_dds, &qdr_dds, 1);
	dds = (struct txdds_ent *)(ppd->link_speed_active == QIB_IB_QDR ?
		qdr_dds : (ppd->link_speed_active == QIB_IB_DDR ?
				ddr_dds : sdr_dds));
	write_tx_serdes_param(ppd, dds);
}