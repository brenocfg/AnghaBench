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
typedef  int u32 ;
struct mxl {TYPE_1__* base; int /*<<< orphan*/  i2cdev; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int MXL_HYDRA_DEVICE_542 ; 
 int MXL_HYDRA_DEVICE_544 ; 
 int MXL_HYDRA_DEVICE_581 ; 
 int MXL_HYDRA_DEVICE_581S ; 
 int MXL_HYDRA_DEVICE_582 ; 
 int MXL_HYDRA_DEVICE_584 ; 
#define  MXL_HYDRA_SKU_ID_544 131 
#define  MXL_HYDRA_SKU_ID_581 130 
#define  MXL_HYDRA_SKU_ID_582 129 
#define  MXL_HYDRA_SKU_ID_584 128 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int read_by_mnemonic (struct mxl*,int,int,int,int*) ; 

__attribute__((used)) static int validate_sku(struct mxl *state)
{
	u32 pad_mux_bond = 0, prcm_chip_id = 0, prcm_so_cid = 0;
	int status;
	u32 type = state->base->type;

	status = read_by_mnemonic(state, 0x90000190, 0, 3, &pad_mux_bond);
	status |= read_by_mnemonic(state, 0x80030000, 0, 12, &prcm_chip_id);
	status |= read_by_mnemonic(state, 0x80030004, 24, 8, &prcm_so_cid);
	if (status)
		return -1;

	dev_info(state->i2cdev, "padMuxBond=%08x, prcmChipId=%08x, prcmSoCId=%08x\n",
		pad_mux_bond, prcm_chip_id, prcm_so_cid);

	if (prcm_chip_id != 0x560) {
		switch (pad_mux_bond) {
		case MXL_HYDRA_SKU_ID_581:
			if (type == MXL_HYDRA_DEVICE_581)
				return 0;
			if (type == MXL_HYDRA_DEVICE_581S) {
				state->base->type = MXL_HYDRA_DEVICE_581;
				return 0;
			}
			break;
		case MXL_HYDRA_SKU_ID_584:
			if (type == MXL_HYDRA_DEVICE_584)
				return 0;
			break;
		case MXL_HYDRA_SKU_ID_544:
			if (type == MXL_HYDRA_DEVICE_544)
				return 0;
			if (type == MXL_HYDRA_DEVICE_542)
				return 0;
			break;
		case MXL_HYDRA_SKU_ID_582:
			if (type == MXL_HYDRA_DEVICE_582)
				return 0;
			break;
		default:
			return -1;
		}
	} else {

	}
	return -1;
}