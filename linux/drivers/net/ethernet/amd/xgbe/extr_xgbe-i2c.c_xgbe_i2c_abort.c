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
 int /*<<< orphan*/  ABORT ; 
 int EBUSY ; 
 int /*<<< orphan*/  EN ; 
 int /*<<< orphan*/  IC_ENABLE ; 
 unsigned int XGBE_ABORT_COUNT ; 
 int /*<<< orphan*/  XI2C_IOREAD_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XI2C_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int xgbe_i2c_abort(struct xgbe_prv_data *pdata)
{
	unsigned int wait = XGBE_ABORT_COUNT;

	/* Must be enabled to recognize the abort request */
	XI2C_IOWRITE_BITS(pdata, IC_ENABLE, EN, 1);

	/* Issue the abort */
	XI2C_IOWRITE_BITS(pdata, IC_ENABLE, ABORT, 1);

	while (wait--) {
		if (!XI2C_IOREAD_BITS(pdata, IC_ENABLE, ABORT))
			return 0;

		usleep_range(500, 600);
	}

	return -EBUSY;
}