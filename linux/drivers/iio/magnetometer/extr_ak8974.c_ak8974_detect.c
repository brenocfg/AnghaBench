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
typedef  int /*<<< orphan*/  u16 ;
struct ak8974 {char const* name; unsigned int variant; TYPE_1__* i2c; int /*<<< orphan*/  map; } ;
typedef  int /*<<< orphan*/  sn ;
typedef  int /*<<< orphan*/  fab_data2 ;
typedef  int /*<<< orphan*/  fab_data1 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK8974_WHOAMI ; 
#define  AK8974_WHOAMI_VALUE_AK8974 130 
#define  AK8974_WHOAMI_VALUE_AMI305 129 
#define  AK8974_WHOAMI_VALUE_AMI306 128 
 int /*<<< orphan*/  AMI305_SN ; 
 int /*<<< orphan*/  AMI305_VER ; 
 int /*<<< orphan*/  AMI306_FINEOUTPUT_X ; 
 int /*<<< orphan*/  AMI306_OFFZERO_X ; 
 int ENODEV ; 
 int /*<<< orphan*/  add_device_randomness (int /*<<< orphan*/ *,int) ; 
 int ak8974_get_u16_val (struct ak8974*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ak8974_read_calib_data (struct ak8974*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int ak8974_detect(struct ak8974 *ak8974)
{
	unsigned int whoami;
	const char *name;
	int ret;
	unsigned int fw;
	u16 sn;

	ret = regmap_read(ak8974->map, AK8974_WHOAMI, &whoami);
	if (ret)
		return ret;

	name = "ami305";

	switch (whoami) {
	case AK8974_WHOAMI_VALUE_AMI306:
		name = "ami306";
		/* fall-through */
	case AK8974_WHOAMI_VALUE_AMI305:
		ret = regmap_read(ak8974->map, AMI305_VER, &fw);
		if (ret)
			return ret;
		fw &= 0x7f; /* only bits 0 thru 6 valid */
		ret = ak8974_get_u16_val(ak8974, AMI305_SN, &sn);
		if (ret)
			return ret;
		add_device_randomness(&sn, sizeof(sn));
		dev_info(&ak8974->i2c->dev,
			 "detected %s, FW ver %02x, S/N: %04x\n",
			 name, fw, sn);
		break;
	case AK8974_WHOAMI_VALUE_AK8974:
		name = "ak8974";
		dev_info(&ak8974->i2c->dev, "detected AK8974\n");
		break;
	default:
		dev_err(&ak8974->i2c->dev, "unsupported device (%02x) ",
			whoami);
		return -ENODEV;
	}

	ak8974->name = name;
	ak8974->variant = whoami;

	if (whoami == AK8974_WHOAMI_VALUE_AMI306) {
		__le16 fab_data1[9], fab_data2[3];
		int i;

		ak8974_read_calib_data(ak8974, AMI306_FINEOUTPUT_X,
				       fab_data1, sizeof(fab_data1));
		ak8974_read_calib_data(ak8974, AMI306_OFFZERO_X,
				       fab_data2, sizeof(fab_data2));

		for (i = 0; i < 3; ++i) {
			static const char axis[3] = "XYZ";
			static const char pgaxis[6] = "ZYZXYX";
			unsigned offz = le16_to_cpu(fab_data2[i]) & 0x7F;
			unsigned fine = le16_to_cpu(fab_data1[i]);
			unsigned sens = le16_to_cpu(fab_data1[i + 3]);
			unsigned pgain1 = le16_to_cpu(fab_data1[i + 6]);
			unsigned pgain2 = pgain1 >> 8;

			pgain1 &= 0xFF;

			dev_info(&ak8974->i2c->dev,
				 "factory calibration for axis %c: offz=%u sens=%u fine=%u pga%c=%u pga%c=%u\n",
				 axis[i], offz, sens, fine, pgaxis[i * 2],
				 pgain1, pgaxis[i * 2 + 1], pgain2);
		}
	}

	return 0;
}