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
typedef  int u8 ;
struct vivid_dev {struct cec_adapter** cec_tx_adap; struct cec_adapter* cec_rx_adap; } ;
struct cec_adapter {scalar_t__ is_configured; } ;

/* Variables and functions */
 unsigned int MAX_OUTPUTS ; 
 scalar_t__ cec_has_log_addr (struct cec_adapter*,int) ; 

__attribute__((used)) static bool vivid_cec_find_dest_adap(struct vivid_dev *dev,
				     struct cec_adapter *adap, u8 dest)
{
	unsigned int i;

	if (dest >= 0xf)
		return false;

	if (adap != dev->cec_rx_adap && dev->cec_rx_adap &&
	    dev->cec_rx_adap->is_configured &&
	    cec_has_log_addr(dev->cec_rx_adap, dest))
		return true;

	for (i = 0; i < MAX_OUTPUTS && dev->cec_tx_adap[i]; i++) {
		if (adap == dev->cec_tx_adap[i])
			continue;
		if (!dev->cec_tx_adap[i]->is_configured)
			continue;
		if (cec_has_log_addr(dev->cec_tx_adap[i], dest))
			return true;
	}
	return false;
}