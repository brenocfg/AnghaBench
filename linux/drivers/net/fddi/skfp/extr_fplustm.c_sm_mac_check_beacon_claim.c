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
struct s_smc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_IMSK2U ; 
 int /*<<< orphan*/  formac_rcv_restart (struct s_smc*) ; 
 int mac_beacon_imsk2u ; 
 int mac_imsk2u ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_receive (struct s_smc*) ; 

void sm_mac_check_beacon_claim(struct s_smc *smc)
{
	/* set formac IMSK : 0 enables irq */
	outpw(FM_A(FM_IMSK2U),~(mac_imsk2u | mac_beacon_imsk2u)) ;
	/* the driver must receive the directed beacons */
	formac_rcv_restart(smc) ;
	process_receive(smc) ;
}