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
struct scom_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SCOM_MAX_IND_RETRIES ; 
 int SCOM_PIB_BLOCKED ; 
 int SCOM_STATUS_ANY_ERR ; 
 int SCOM_STATUS_PIB_RESP_SHIFT ; 
 int XSCOM_ADDR_DIRECT_PART ; 
 int XSCOM_ADDR_INDIRECT_PART ; 
 int XSCOM_DATA_IND_COMPLETE ; 
 int XSCOM_DATA_IND_DATA ; 
 int XSCOM_DATA_IND_ERR_MASK ; 
 int XSCOM_DATA_IND_ERR_SHIFT ; 
 int __get_scom (struct scom_device*,int*,int,int*) ; 
 int __put_scom (struct scom_device*,int,int,int*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int put_indirect_scom_form0(struct scom_device *scom, uint64_t value,
				   uint64_t addr, uint32_t *status)
{
	uint64_t ind_data, ind_addr;
	int rc, retries, err = 0;

	if (value & ~XSCOM_DATA_IND_DATA)
		return -EINVAL;

	ind_addr = addr & XSCOM_ADDR_DIRECT_PART;
	ind_data = (addr & XSCOM_ADDR_INDIRECT_PART) | value;
	rc = __put_scom(scom, ind_data, ind_addr, status);
	if (rc || (*status & SCOM_STATUS_ANY_ERR))
		return rc;

	for (retries = 0; retries < SCOM_MAX_IND_RETRIES; retries++) {
		rc = __get_scom(scom, &ind_data, addr, status);
		if (rc || (*status & SCOM_STATUS_ANY_ERR))
			return rc;

		err = (ind_data & XSCOM_DATA_IND_ERR_MASK) >> XSCOM_DATA_IND_ERR_SHIFT;
		*status = err << SCOM_STATUS_PIB_RESP_SHIFT;
		if ((ind_data & XSCOM_DATA_IND_COMPLETE) || (err != SCOM_PIB_BLOCKED))
			return 0;

		msleep(1);
	}
	return rc;
}