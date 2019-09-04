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
struct xgbe_prv_data {unsigned int rx_q_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTL_Q_RQOMR ; 
 int /*<<< orphan*/  RSF ; 
 int /*<<< orphan*/  XGMAC_MTL_IOWRITE_BITS (struct xgbe_prv_data*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int xgbe_config_rsf_mode(struct xgbe_prv_data *pdata, unsigned int val)
{
	unsigned int i;

	for (i = 0; i < pdata->rx_q_count; i++)
		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_Q_RQOMR, RSF, val);

	return 0;
}