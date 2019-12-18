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
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_2__ {int* extra_capability; } ;

/* Variables and functions */
 int QLCNIC_83XX_FW_CAPAB_ENCAP_TX_OFFLOAD ; 

__attribute__((used)) static inline bool qlcnic_83xx_encap_tx_offload(struct qlcnic_adapter *adapter)
{
	return adapter->ahw->extra_capability[0] &
	       QLCNIC_83XX_FW_CAPAB_ENCAP_TX_OFFLOAD;
}