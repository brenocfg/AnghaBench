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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR ; 
 int CSR_RPO ; 
 int CSR_TPO0 ; 
 int CSR_TPO1 ; 
 int CSR_TPO2 ; 
 int CSR_TPO3 ; 
 int /*<<< orphan*/  TCCR ; 
 int TCCR_TSRQ0 ; 
 int TCCR_TSRQ1 ; 
 int TCCR_TSRQ2 ; 
 int TCCR_TSRQ3 ; 
 int ravb_config (struct net_device*) ; 
 int /*<<< orphan*/  ravb_rcv_snd_disable (struct net_device*) ; 
 int ravb_wait (struct net_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ravb_stop_dma(struct net_device *ndev)
{
	int error;

	/* Wait for stopping the hardware TX process */
	error = ravb_wait(ndev, TCCR,
			  TCCR_TSRQ0 | TCCR_TSRQ1 | TCCR_TSRQ2 | TCCR_TSRQ3, 0);
	if (error)
		return error;

	error = ravb_wait(ndev, CSR, CSR_TPO0 | CSR_TPO1 | CSR_TPO2 | CSR_TPO3,
			  0);
	if (error)
		return error;

	/* Stop the E-MAC's RX/TX processes. */
	ravb_rcv_snd_disable(ndev);

	/* Wait for stopping the RX DMA process */
	error = ravb_wait(ndev, CSR, CSR_RPO, 0);
	if (error)
		return error;

	/* Stop AVB-DMAC process */
	return ravb_config(ndev);
}