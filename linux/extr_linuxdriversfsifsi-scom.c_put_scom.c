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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct scom_device {int /*<<< orphan*/  fsi_dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  SCOM_FSI2PIB_RESET_REG ; 
 int SCOM_MAX_RETRIES ; 
 int SCOM_STATUS_PIB_RESP_MASK ; 
 int SCOM_STATUS_PIB_RESP_SHIFT ; 
 int /*<<< orphan*/  fsi_device_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int handle_fsi2pib_status (struct scom_device*,int) ; 
 int handle_pib_status (struct scom_device*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int raw_put_scom (struct scom_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int put_scom(struct scom_device *scom, uint64_t value,
		    uint64_t addr)
{
	uint32_t status, dummy = -1;
	int rc, retries;

	for (retries = 0; retries < SCOM_MAX_RETRIES; retries++) {
		rc = raw_put_scom(scom, value, addr, &status);
		if (rc) {
			/* Try resetting the bridge if FSI fails */
			if (rc != -ENODEV && retries == 0) {
				fsi_device_write(scom->fsi_dev, SCOM_FSI2PIB_RESET_REG,
						 &dummy, sizeof(uint32_t));
				rc = -EBUSY;
			} else
				return rc;
		} else
			rc = handle_fsi2pib_status(scom, status);
		if (rc && rc != -EBUSY)
			break;
		if (rc == 0) {
			rc = handle_pib_status(scom,
					       (status & SCOM_STATUS_PIB_RESP_MASK)
					       >> SCOM_STATUS_PIB_RESP_SHIFT);
			if (rc && rc != -EBUSY)
				break;
		}
		if (rc == 0)
			break;
		msleep(1);
	}
	return rc;
}