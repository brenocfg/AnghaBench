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
struct xgbe_prv_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 int /*<<< orphan*/  DMA_MR ; 
 int EBUSY ; 
 int /*<<< orphan*/  SWR ; 
 scalar_t__ XGMAC_IOREAD_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int __xgbe_exit(struct xgbe_prv_data *pdata)
{
	unsigned int count = 2000;

	DBGPR("-->xgbe_exit\n");

	/* Issue a software reset */
	XGMAC_IOWRITE_BITS(pdata, DMA_MR, SWR, 1);
	usleep_range(10, 15);

	/* Poll Until Poll Condition */
	while (--count && XGMAC_IOREAD_BITS(pdata, DMA_MR, SWR))
		usleep_range(500, 600);

	if (!count)
		return -EBUSY;

	DBGPR("<--xgbe_exit\n");

	return 0;
}