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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct scom_device {int /*<<< orphan*/  fsi_dev; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  SCOM_CMD_REG ; 
 int /*<<< orphan*/  SCOM_DATA0_REG ; 
 int /*<<< orphan*/  SCOM_DATA1_REG ; 
 int /*<<< orphan*/  SCOM_STATUS_REG ; 
 int SCOM_WRITE_CMD ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int fsi_device_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int fsi_device_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int __put_scom(struct scom_device *scom_dev, uint64_t value,
		      uint32_t addr, uint32_t *status)
{
	__be32 data, raw_status;
	int rc;

	data = cpu_to_be32((value >> 32) & 0xffffffff);
	rc = fsi_device_write(scom_dev->fsi_dev, SCOM_DATA0_REG, &data,
				sizeof(uint32_t));
	if (rc)
		return rc;

	data = cpu_to_be32(value & 0xffffffff);
	rc = fsi_device_write(scom_dev->fsi_dev, SCOM_DATA1_REG, &data,
				sizeof(uint32_t));
	if (rc)
		return rc;

	data = cpu_to_be32(SCOM_WRITE_CMD | addr);
	rc = fsi_device_write(scom_dev->fsi_dev, SCOM_CMD_REG, &data,
				sizeof(uint32_t));
	if (rc)
		return rc;
	rc = fsi_device_read(scom_dev->fsi_dev, SCOM_STATUS_REG, &raw_status,
			     sizeof(uint32_t));
	if (rc)
		return rc;
	*status = be32_to_cpu(raw_status);

	return 0;
}