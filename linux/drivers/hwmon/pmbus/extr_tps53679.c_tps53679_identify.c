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
typedef  int u8 ;
struct pmbus_driver_info {int /*<<< orphan*/  vrm_version; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMBUS_VOUT_MODE ; 
#define  TPS53679_PROT_IMVP8_5MV 132 
#define  TPS53679_PROT_VR12_5MV 131 
#define  TPS53679_PROT_VR12_5_10MV 130 
#define  TPS53679_PROT_VR13_10MV 129 
#define  TPS53679_PROT_VR13_5MV 128 
 int pmbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vr12 ; 
 int /*<<< orphan*/  vr13 ; 

__attribute__((used)) static int tps53679_identify(struct i2c_client *client,
			     struct pmbus_driver_info *info)
{
	u8 vout_params;
	int ret;

	/* Read the register with VOUT scaling value.*/
	ret = pmbus_read_byte_data(client, 0, PMBUS_VOUT_MODE);
	if (ret < 0)
		return ret;

	vout_params = ret & GENMASK(4, 0);

	switch (vout_params) {
	case TPS53679_PROT_VR13_10MV:
	case TPS53679_PROT_VR12_5_10MV:
		info->vrm_version = vr13;
		break;
	case TPS53679_PROT_VR13_5MV:
	case TPS53679_PROT_VR12_5MV:
	case TPS53679_PROT_IMVP8_5MV:
		info->vrm_version = vr12;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}