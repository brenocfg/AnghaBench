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
typedef  scalar_t__ u64 ;
struct xgbe_prv_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_STNR ; 
 int /*<<< orphan*/  MAC_STSR ; 
 scalar_t__ NSEC_PER_SEC ; 
 scalar_t__ XGMAC_IOREAD (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 xgbe_get_tstamp_time(struct xgbe_prv_data *pdata)
{
	u64 nsec;

	nsec = XGMAC_IOREAD(pdata, MAC_STSR);
	nsec *= NSEC_PER_SEC;
	nsec += XGMAC_IOREAD(pdata, MAC_STNR);

	return nsec;
}