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
typedef  int /*<<< orphan*/  u16 ;
struct rcar_csi2 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int PHTW_CWEN ; 
 int PHTW_DWEN ; 
 int /*<<< orphan*/  PHTW_REG ; 
 int PHTW_TESTDIN_CODE (int /*<<< orphan*/ ) ; 
 int PHTW_TESTDIN_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int rcsi2_read (struct rcar_csi2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcsi2_write (struct rcar_csi2*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int rcsi2_phtw_write(struct rcar_csi2 *priv, u16 data, u16 code)
{
	unsigned int timeout;

	rcsi2_write(priv, PHTW_REG,
		    PHTW_DWEN | PHTW_TESTDIN_DATA(data) |
		    PHTW_CWEN | PHTW_TESTDIN_CODE(code));

	/* Wait for DWEN and CWEN to be cleared by hardware. */
	for (timeout = 0; timeout <= 20; timeout++) {
		if (!(rcsi2_read(priv, PHTW_REG) & (PHTW_DWEN | PHTW_CWEN)))
			return 0;

		usleep_range(1000, 2000);
	}

	dev_err(priv->dev, "Timeout waiting for PHTW_DWEN and/or PHTW_CWEN\n");

	return -ETIMEDOUT;
}