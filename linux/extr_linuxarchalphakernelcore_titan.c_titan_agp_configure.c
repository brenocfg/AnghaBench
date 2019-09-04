#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int apctl_v_agp_rate; int apctl_v_agp_hp_rd; int apctl_v_agp_lp_rd; scalar_t__ apctl_v_agp_sba_en; int /*<<< orphan*/  apctl_v_agp_en; } ;
union TPAchipPCTL {int /*<<< orphan*/  pctl_q_whole; TYPE_3__ pctl_r_bits; } ;
struct TYPE_11__ {int /*<<< orphan*/  csr; } ;
struct TYPE_12__ {TYPE_4__ pctl; } ;
typedef  TYPE_5__ titan_pachip_port ;
struct TYPE_8__ {int rate; int /*<<< orphan*/  enable; scalar_t__ sba; } ;
struct TYPE_9__ {TYPE_1__ bits; } ;
struct TYPE_13__ {TYPE_2__ mode; TYPE_5__* private; } ;
typedef  TYPE_6__ alpha_agp_info ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,int,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
titan_agp_configure(alpha_agp_info *agp)
{
	union TPAchipPCTL pctl;
	titan_pachip_port *port = agp->private;
	pctl.pctl_q_whole = port->pctl.csr;

	/* Side-Band Addressing? */
	pctl.pctl_r_bits.apctl_v_agp_sba_en = agp->mode.bits.sba;

	/* AGP Rate? */
	pctl.pctl_r_bits.apctl_v_agp_rate = 0;		/* 1x */
	if (agp->mode.bits.rate & 2) 
		pctl.pctl_r_bits.apctl_v_agp_rate = 1;	/* 2x */
#if 0
	if (agp->mode.bits.rate & 4) 
		pctl.pctl_r_bits.apctl_v_agp_rate = 2;	/* 4x */
#endif
	
	/* RQ Depth? */
	pctl.pctl_r_bits.apctl_v_agp_hp_rd = 2;
	pctl.pctl_r_bits.apctl_v_agp_lp_rd = 7;

	/*
	 * AGP Enable.
	 */
	pctl.pctl_r_bits.apctl_v_agp_en = agp->mode.bits.enable;

	/* Tell the user.  */
	printk("Enabling AGP: %dX%s\n", 
	       1 << pctl.pctl_r_bits.apctl_v_agp_rate,
	       pctl.pctl_r_bits.apctl_v_agp_sba_en ? " - SBA" : "");
	       
	/* Write it.  */
	port->pctl.csr = pctl.pctl_q_whole;
	
	/* And wait at least 5000 66MHz cycles (per Titan spec).  */
	udelay(100);

	return 0;
}