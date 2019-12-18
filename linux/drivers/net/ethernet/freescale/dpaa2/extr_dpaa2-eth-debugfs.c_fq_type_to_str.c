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
struct dpaa2_eth_fq {int type; } ;

/* Variables and functions */
#define  DPAA2_RX_FQ 129 
#define  DPAA2_TX_CONF_FQ 128 

__attribute__((used)) static char *fq_type_to_str(struct dpaa2_eth_fq *fq)
{
	switch (fq->type) {
	case DPAA2_RX_FQ:
		return "Rx";
	case DPAA2_TX_CONF_FQ:
		return "Tx conf";
	default:
		return "N/A";
	}
}