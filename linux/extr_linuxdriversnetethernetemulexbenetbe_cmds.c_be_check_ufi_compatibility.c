#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct flash_file_hdr_g3 {int* build; int asic_type_rev; } ;
struct be_adapter {int asic_rev; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE2_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  BE3_chip (struct be_adapter*) ; 
 scalar_t__ BEx_chip (struct be_adapter*) ; 
#define  BLD_STR_UFI_TYPE_BE2 130 
#define  BLD_STR_UFI_TYPE_BE3 129 
#define  BLD_STR_UFI_TYPE_SH 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  skyhawk_chip (struct be_adapter*) ; 

__attribute__((used)) static bool be_check_ufi_compatibility(struct be_adapter *adapter,
				       struct flash_file_hdr_g3 *fhdr)
{
	if (!fhdr) {
		dev_err(&adapter->pdev->dev, "Invalid FW UFI file");
		return false;
	}

	/* First letter of the build version is used to identify
	 * which chip this image file is meant for.
	 */
	switch (fhdr->build[0]) {
	case BLD_STR_UFI_TYPE_SH:
		if (!skyhawk_chip(adapter))
			return false;
		break;
	case BLD_STR_UFI_TYPE_BE3:
		if (!BE3_chip(adapter))
			return false;
		break;
	case BLD_STR_UFI_TYPE_BE2:
		if (!BE2_chip(adapter))
			return false;
		break;
	default:
		return false;
	}

	/* In BE3 FW images the "asic_type_rev" field doesn't track the
	 * asic_rev of the chips it is compatible with.
	 * When asic_type_rev is 0 the image is compatible only with
	 * pre-BE3-R chips (asic_rev < 0x10)
	 */
	if (BEx_chip(adapter) && fhdr->asic_type_rev == 0)
		return adapter->asic_rev < 0x10;
	else
		return (fhdr->asic_type_rev >= adapter->asic_rev);
}