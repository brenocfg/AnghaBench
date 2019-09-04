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
 int EINVAL ; 
 int /*<<< orphan*/  MAC_TCR ; 
#define  SPEED_1000 130 
#define  SPEED_10000 129 
#define  SPEED_2500 128 
 int /*<<< orphan*/  SS ; 
 unsigned int XGMAC_IOREAD_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int xgbe_set_speed(struct xgbe_prv_data *pdata, int speed)
{
	unsigned int ss;

	switch (speed) {
	case SPEED_1000:
		ss = 0x03;
		break;
	case SPEED_2500:
		ss = 0x02;
		break;
	case SPEED_10000:
		ss = 0x00;
		break;
	default:
		return -EINVAL;
	}

	if (XGMAC_IOREAD_BITS(pdata, MAC_TCR, SS) != ss)
		XGMAC_IOWRITE_BITS(pdata, MAC_TCR, SS, ss);

	return 0;
}