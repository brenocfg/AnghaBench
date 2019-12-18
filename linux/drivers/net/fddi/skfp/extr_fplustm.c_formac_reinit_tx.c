#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* a; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_s_size; } ;
struct TYPE_7__ {TYPE_1__ fifo; } ;
struct TYPE_8__ {TYPE_2__ fp; } ;
struct s_smc {TYPE_5__ mib; TYPE_3__ hw; } ;
struct TYPE_9__ {scalar_t__ fddiPATHSbaPayload; } ;

/* Variables and functions */
 size_t PATH0 ; 
 int /*<<< orphan*/  init_mac (struct s_smc*,int /*<<< orphan*/ ) ; 

void formac_reinit_tx(struct s_smc *smc)
{
	/*
	 * Split up the FIFO and reinitialize the MAC if synchronous
	 * bandwidth becomes available but no synchronous queue is
	 * configured.
	 */
	if (!smc->hw.fp.fifo.tx_s_size && smc->mib.a[PATH0].fddiPATHSbaPayload){
		(void)init_mac(smc,0) ;
	}
}