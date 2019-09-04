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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct radeon_device {int family; TYPE_1__* smc_fw; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BARTS_SMC_INT_VECTOR_SIZE ; 
 int /*<<< orphan*/  BARTS_SMC_INT_VECTOR_START ; 
 int /*<<< orphan*/  BARTS_SMC_UCODE_SIZE ; 
 int /*<<< orphan*/  BARTS_SMC_UCODE_START ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CAICOS_SMC_INT_VECTOR_SIZE ; 
 int /*<<< orphan*/  CAICOS_SMC_INT_VECTOR_START ; 
 int /*<<< orphan*/  CAICOS_SMC_UCODE_SIZE ; 
 int /*<<< orphan*/  CAICOS_SMC_UCODE_START ; 
 int /*<<< orphan*/  CAYMAN_SMC_INT_VECTOR_SIZE ; 
 int /*<<< orphan*/  CAYMAN_SMC_INT_VECTOR_START ; 
 int /*<<< orphan*/  CAYMAN_SMC_UCODE_SIZE ; 
 int /*<<< orphan*/  CAYMAN_SMC_UCODE_START ; 
 int /*<<< orphan*/  CEDAR_SMC_INT_VECTOR_SIZE ; 
 int /*<<< orphan*/  CEDAR_SMC_INT_VECTOR_START ; 
 int /*<<< orphan*/  CEDAR_SMC_UCODE_SIZE ; 
 int /*<<< orphan*/  CEDAR_SMC_UCODE_START ; 
#define  CHIP_BARTS 140 
#define  CHIP_CAICOS 139 
#define  CHIP_CAYMAN 138 
#define  CHIP_CEDAR 137 
#define  CHIP_CYPRESS 136 
#define  CHIP_HEMLOCK 135 
#define  CHIP_JUNIPER 134 
#define  CHIP_REDWOOD 133 
#define  CHIP_RV710 132 
#define  CHIP_RV730 131 
#define  CHIP_RV740 130 
#define  CHIP_RV770 129 
#define  CHIP_TURKS 128 
 int /*<<< orphan*/  CYPRESS_SMC_INT_VECTOR_SIZE ; 
 int /*<<< orphan*/  CYPRESS_SMC_INT_VECTOR_START ; 
 int /*<<< orphan*/  CYPRESS_SMC_UCODE_SIZE ; 
 int /*<<< orphan*/  CYPRESS_SMC_UCODE_START ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  JUNIPER_SMC_INT_VECTOR_SIZE ; 
 int /*<<< orphan*/  JUNIPER_SMC_INT_VECTOR_START ; 
 int /*<<< orphan*/  JUNIPER_SMC_UCODE_SIZE ; 
 int /*<<< orphan*/  JUNIPER_SMC_UCODE_START ; 
 int /*<<< orphan*/  REDWOOD_SMC_INT_VECTOR_SIZE ; 
 int /*<<< orphan*/  REDWOOD_SMC_INT_VECTOR_START ; 
 int /*<<< orphan*/  REDWOOD_SMC_UCODE_SIZE ; 
 int /*<<< orphan*/  REDWOOD_SMC_UCODE_START ; 
 int /*<<< orphan*/  RV710_SMC_INT_VECTOR_SIZE ; 
 int /*<<< orphan*/  RV710_SMC_INT_VECTOR_START ; 
 int /*<<< orphan*/  RV710_SMC_UCODE_SIZE ; 
 int /*<<< orphan*/  RV710_SMC_UCODE_START ; 
 int /*<<< orphan*/  RV730_SMC_INT_VECTOR_SIZE ; 
 int /*<<< orphan*/  RV730_SMC_INT_VECTOR_START ; 
 int /*<<< orphan*/  RV730_SMC_UCODE_SIZE ; 
 int /*<<< orphan*/  RV730_SMC_UCODE_START ; 
 int /*<<< orphan*/  RV740_SMC_INT_VECTOR_SIZE ; 
 int /*<<< orphan*/  RV740_SMC_INT_VECTOR_START ; 
 int /*<<< orphan*/  RV740_SMC_UCODE_SIZE ; 
 int /*<<< orphan*/  RV740_SMC_UCODE_START ; 
 int /*<<< orphan*/  RV770_SMC_INT_VECTOR_SIZE ; 
 int /*<<< orphan*/  RV770_SMC_INT_VECTOR_START ; 
 int /*<<< orphan*/  RV770_SMC_UCODE_SIZE ; 
 int /*<<< orphan*/  RV770_SMC_UCODE_START ; 
 int /*<<< orphan*/  TURKS_SMC_INT_VECTOR_SIZE ; 
 int /*<<< orphan*/  TURKS_SMC_INT_VECTOR_START ; 
 int /*<<< orphan*/  TURKS_SMC_UCODE_SIZE ; 
 int /*<<< orphan*/  TURKS_SMC_UCODE_START ; 
 int /*<<< orphan*/  barts_smc_int_vectors ; 
 int /*<<< orphan*/  caicos_smc_int_vectors ; 
 int /*<<< orphan*/  cayman_smc_int_vectors ; 
 int /*<<< orphan*/  cedar_smc_int_vectors ; 
 int /*<<< orphan*/  cypress_smc_int_vectors ; 
 int /*<<< orphan*/  juniper_smc_int_vectors ; 
 int /*<<< orphan*/  redwood_smc_int_vectors ; 
 int /*<<< orphan*/  rv710_smc_int_vectors ; 
 int /*<<< orphan*/  rv730_smc_int_vectors ; 
 int /*<<< orphan*/  rv740_smc_int_vectors ; 
 int /*<<< orphan*/  rv770_clear_smc_sram (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int rv770_copy_bytes_to_smc (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rv770_program_interrupt_vectors (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv770_smc_int_vectors ; 
 int /*<<< orphan*/  turks_smc_int_vectors ; 

int rv770_load_smc_ucode(struct radeon_device *rdev,
			 u16 limit)
{
	int ret;
	const u8 *int_vect;
	u16 int_vect_start_address;
	u16 int_vect_size;
	const u8 *ucode_data;
	u16 ucode_start_address;
	u16 ucode_size;

	if (!rdev->smc_fw)
		return -EINVAL;

	rv770_clear_smc_sram(rdev, limit);

	switch (rdev->family) {
	case CHIP_RV770:
		ucode_start_address = RV770_SMC_UCODE_START;
		ucode_size = RV770_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&rv770_smc_int_vectors;
		int_vect_start_address = RV770_SMC_INT_VECTOR_START;
		int_vect_size = RV770_SMC_INT_VECTOR_SIZE;
		break;
	case CHIP_RV730:
		ucode_start_address = RV730_SMC_UCODE_START;
		ucode_size = RV730_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&rv730_smc_int_vectors;
		int_vect_start_address = RV730_SMC_INT_VECTOR_START;
		int_vect_size = RV730_SMC_INT_VECTOR_SIZE;
		break;
	case CHIP_RV710:
		ucode_start_address = RV710_SMC_UCODE_START;
		ucode_size = RV710_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&rv710_smc_int_vectors;
		int_vect_start_address = RV710_SMC_INT_VECTOR_START;
		int_vect_size = RV710_SMC_INT_VECTOR_SIZE;
		break;
	case CHIP_RV740:
		ucode_start_address = RV740_SMC_UCODE_START;
		ucode_size = RV740_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&rv740_smc_int_vectors;
		int_vect_start_address = RV740_SMC_INT_VECTOR_START;
		int_vect_size = RV740_SMC_INT_VECTOR_SIZE;
		break;
	case CHIP_CEDAR:
		ucode_start_address = CEDAR_SMC_UCODE_START;
		ucode_size = CEDAR_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&cedar_smc_int_vectors;
		int_vect_start_address = CEDAR_SMC_INT_VECTOR_START;
		int_vect_size = CEDAR_SMC_INT_VECTOR_SIZE;
		break;
	case CHIP_REDWOOD:
		ucode_start_address = REDWOOD_SMC_UCODE_START;
		ucode_size = REDWOOD_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&redwood_smc_int_vectors;
		int_vect_start_address = REDWOOD_SMC_INT_VECTOR_START;
		int_vect_size = REDWOOD_SMC_INT_VECTOR_SIZE;
		break;
	case CHIP_JUNIPER:
		ucode_start_address = JUNIPER_SMC_UCODE_START;
		ucode_size = JUNIPER_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&juniper_smc_int_vectors;
		int_vect_start_address = JUNIPER_SMC_INT_VECTOR_START;
		int_vect_size = JUNIPER_SMC_INT_VECTOR_SIZE;
		break;
	case CHIP_CYPRESS:
	case CHIP_HEMLOCK:
		ucode_start_address = CYPRESS_SMC_UCODE_START;
		ucode_size = CYPRESS_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&cypress_smc_int_vectors;
		int_vect_start_address = CYPRESS_SMC_INT_VECTOR_START;
		int_vect_size = CYPRESS_SMC_INT_VECTOR_SIZE;
		break;
	case CHIP_BARTS:
		ucode_start_address = BARTS_SMC_UCODE_START;
		ucode_size = BARTS_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&barts_smc_int_vectors;
		int_vect_start_address = BARTS_SMC_INT_VECTOR_START;
		int_vect_size = BARTS_SMC_INT_VECTOR_SIZE;
		break;
	case CHIP_TURKS:
		ucode_start_address = TURKS_SMC_UCODE_START;
		ucode_size = TURKS_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&turks_smc_int_vectors;
		int_vect_start_address = TURKS_SMC_INT_VECTOR_START;
		int_vect_size = TURKS_SMC_INT_VECTOR_SIZE;
		break;
	case CHIP_CAICOS:
		ucode_start_address = CAICOS_SMC_UCODE_START;
		ucode_size = CAICOS_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&caicos_smc_int_vectors;
		int_vect_start_address = CAICOS_SMC_INT_VECTOR_START;
		int_vect_size = CAICOS_SMC_INT_VECTOR_SIZE;
		break;
	case CHIP_CAYMAN:
		ucode_start_address = CAYMAN_SMC_UCODE_START;
		ucode_size = CAYMAN_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&cayman_smc_int_vectors;
		int_vect_start_address = CAYMAN_SMC_INT_VECTOR_START;
		int_vect_size = CAYMAN_SMC_INT_VECTOR_SIZE;
		break;
	default:
		DRM_ERROR("unknown asic in smc ucode loader\n");
		BUG();
	}

	/* load the ucode */
	ucode_data = (const u8 *)rdev->smc_fw->data;
	ret = rv770_copy_bytes_to_smc(rdev, ucode_start_address,
				      ucode_data, ucode_size, limit);
	if (ret)
		return ret;

	/* set up the int vectors */
	ret = rv770_program_interrupt_vectors(rdev, int_vect_start_address,
					      int_vect, int_vect_size);
	if (ret)
		return ret;

	return 0;
}