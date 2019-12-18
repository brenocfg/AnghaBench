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
struct sh_eth_cpu_data {int fcftr_value; scalar_t__ trscer_err_mask; scalar_t__ eesr_err_check; scalar_t__ tx_check; scalar_t__ fdr_value; scalar_t__ ecsipr_value; scalar_t__ ecsr_value; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_ECSIPR_INIT ; 
 scalar_t__ DEFAULT_ECSR_INIT ; 
 scalar_t__ DEFAULT_EESR_ERR_CHECK ; 
 scalar_t__ DEFAULT_FDR_INIT ; 
 int DEFAULT_FIFO_F_D_RFD ; 
 int DEFAULT_FIFO_F_D_RFF ; 
 scalar_t__ DEFAULT_TRSCER_ERR_MASK ; 
 scalar_t__ DEFAULT_TX_CHECK ; 

__attribute__((used)) static void sh_eth_set_default_cpu_data(struct sh_eth_cpu_data *cd)
{
	if (!cd->ecsr_value)
		cd->ecsr_value = DEFAULT_ECSR_INIT;

	if (!cd->ecsipr_value)
		cd->ecsipr_value = DEFAULT_ECSIPR_INIT;

	if (!cd->fcftr_value)
		cd->fcftr_value = DEFAULT_FIFO_F_D_RFF |
				  DEFAULT_FIFO_F_D_RFD;

	if (!cd->fdr_value)
		cd->fdr_value = DEFAULT_FDR_INIT;

	if (!cd->tx_check)
		cd->tx_check = DEFAULT_TX_CHECK;

	if (!cd->eesr_err_check)
		cd->eesr_err_check = DEFAULT_EESR_ERR_CHECK;

	if (!cd->trscer_err_mask)
		cd->trscer_err_mask = DEFAULT_TRSCER_ERR_MASK;
}