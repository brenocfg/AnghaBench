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
struct isp1704_charger {int /*<<< orphan*/  dev; int /*<<< orphan*/  model; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int ENODEV ; 
 int NXP_VENDOR_ID ; 
 int /*<<< orphan*/  ULPI_PRODUCT_ID_HIGH ; 
 int /*<<< orphan*/  ULPI_PRODUCT_ID_LOW ; 
 int /*<<< orphan*/  ULPI_SCRATCH ; 
 int /*<<< orphan*/  ULPI_VENDOR_ID_HIGH ; 
 int /*<<< orphan*/  ULPI_VENDOR_ID_LOW ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int isp1704_read (struct isp1704_charger*,int /*<<< orphan*/ ) ; 
 int isp1704_write (struct isp1704_charger*,int /*<<< orphan*/ ,int) ; 
 int* isp170x_id ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static inline int isp1704_test_ulpi(struct isp1704_charger *isp)
{
	int vendor;
	int product;
	int i;
	int ret;

	/* Test ULPI interface */
	ret = isp1704_write(isp, ULPI_SCRATCH, 0xaa);
	if (ret < 0)
		return ret;

	ret = isp1704_read(isp, ULPI_SCRATCH);
	if (ret < 0)
		return ret;

	if (ret != 0xaa)
		return -ENODEV;

	/* Verify the product and vendor id matches */
	vendor = isp1704_read(isp, ULPI_VENDOR_ID_LOW);
	vendor |= isp1704_read(isp, ULPI_VENDOR_ID_HIGH) << 8;
	if (vendor != NXP_VENDOR_ID)
		return -ENODEV;

	product = isp1704_read(isp, ULPI_PRODUCT_ID_LOW);
	product |= isp1704_read(isp, ULPI_PRODUCT_ID_HIGH) << 8;

	for (i = 0; i < ARRAY_SIZE(isp170x_id); i++) {
		if (product == isp170x_id[i]) {
			sprintf(isp->model, "isp%x", product);
			return product;
		}
	}

	dev_err(isp->dev, "product id %x not matching known ids", product);

	return -ENODEV;
}