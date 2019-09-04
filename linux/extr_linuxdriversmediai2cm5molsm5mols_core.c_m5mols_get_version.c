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
typedef  int /*<<< orphan*/  u8 ;
struct v4l2_subdev {int dummy; } ;
struct m5mols_version {int /*<<< orphan*/  project; int /*<<< orphan*/  customer; int /*<<< orphan*/  af; int /*<<< orphan*/  awb; int /*<<< orphan*/  param; int /*<<< orphan*/  hw; int /*<<< orphan*/  fw; int /*<<< orphan*/ * str; } ;
struct m5mols_info {struct m5mols_version ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_VERSION ; 
 int /*<<< orphan*/  REG_SAMSUNG_ELECTRO ; 
 int /*<<< orphan*/  REG_SAMSUNG_OPTICS ; 
 int /*<<< orphan*/  REG_SAMSUNG_TECHWIN ; 
 int /*<<< orphan*/  SYSTEM_VER_AWB ; 
 int /*<<< orphan*/  SYSTEM_VER_CUSTOMER ; 
 int /*<<< orphan*/  SYSTEM_VER_FIRMWARE ; 
 int /*<<< orphan*/  SYSTEM_VER_HARDWARE ; 
 int /*<<< orphan*/  SYSTEM_VER_PARAMETER ; 
 int /*<<< orphan*/  SYSTEM_VER_PROJECT ; 
 int /*<<< orphan*/  SYSTEM_VER_STRING ; 
 int VERSION_STRING_SIZE ; 
 int /*<<< orphan*/  is_available_af (struct m5mols_info*) ; 
 scalar_t__ is_manufacturer (struct m5mols_info*,int /*<<< orphan*/ ) ; 
 int m5mols_read_u16 (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int m5mols_read_u8 (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct m5mols_info* to_m5mols (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,...) ; 

__attribute__((used)) static int m5mols_get_version(struct v4l2_subdev *sd)
{
	struct m5mols_info *info = to_m5mols(sd);
	struct m5mols_version *ver = &info->ver;
	u8 *str = ver->str;
	int i;
	int ret;

	ret = m5mols_read_u8(sd, SYSTEM_VER_CUSTOMER, &ver->customer);
	if (!ret)
		ret = m5mols_read_u8(sd, SYSTEM_VER_PROJECT, &ver->project);
	if (!ret)
		ret = m5mols_read_u16(sd, SYSTEM_VER_FIRMWARE, &ver->fw);
	if (!ret)
		ret = m5mols_read_u16(sd, SYSTEM_VER_HARDWARE, &ver->hw);
	if (!ret)
		ret = m5mols_read_u16(sd, SYSTEM_VER_PARAMETER, &ver->param);
	if (!ret)
		ret = m5mols_read_u16(sd, SYSTEM_VER_AWB, &ver->awb);
	if (!ret)
		ret = m5mols_read_u8(sd, AF_VERSION, &ver->af);
	if (ret)
		return ret;

	for (i = 0; i < VERSION_STRING_SIZE; i++) {
		ret = m5mols_read_u8(sd, SYSTEM_VER_STRING, &str[i]);
		if (ret)
			return ret;
	}

	v4l2_info(sd, "Manufacturer\t[%s]\n",
			is_manufacturer(info, REG_SAMSUNG_ELECTRO) ?
			"Samsung Electro-Mechanics" :
			is_manufacturer(info, REG_SAMSUNG_OPTICS) ?
			"Samsung Fiber-Optics" :
			is_manufacturer(info, REG_SAMSUNG_TECHWIN) ?
			"Samsung Techwin" : "None");
	v4l2_info(sd, "Customer/Project\t[0x%02x/0x%02x]\n",
			info->ver.customer, info->ver.project);

	if (!is_available_af(info))
		v4l2_info(sd, "No support Auto Focus on this firmware\n");

	return ret;
}