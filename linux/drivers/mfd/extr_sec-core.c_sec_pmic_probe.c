#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sec_pmic_dev {unsigned long device_type; int /*<<< orphan*/  wakeup; TYPE_1__* dev; struct sec_platform_data* regmap_pmic; struct sec_platform_data* pdata; int /*<<< orphan*/  irq_base; int /*<<< orphan*/  irq; struct i2c_client* i2c; } ;
struct sec_platform_data {unsigned long device_type; int /*<<< orphan*/  (* cfg_pmic_irq ) () ;int /*<<< orphan*/  wakeup; int /*<<< orphan*/  irq_base; } ;
struct regmap_config {int dummy; } ;
struct mfd_cell {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_8__ {scalar_t__ of_node; } ;
struct i2c_client {TYPE_1__ dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct mfd_cell*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct sec_platform_data*) ; 
 int PTR_ERR (struct sec_platform_data*) ; 
#define  S2MPA01 136 
#define  S2MPS11X 135 
#define  S2MPS13X 134 
#define  S2MPS14X 133 
#define  S2MPS15X 132 
#define  S2MPU02 131 
#define  S5M8751X 130 
#define  S5M8763X 129 
#define  S5M8767X 128 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 struct sec_platform_data* dev_get_platdata (TYPE_1__*) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct sec_pmic_dev* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (TYPE_1__*,int,struct mfd_cell const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sec_platform_data* devm_regmap_init_i2c (struct i2c_client*,struct regmap_config const*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct sec_pmic_dev*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_1__*) ; 
 struct mfd_cell* s2mpa01_devs ; 
 struct regmap_config s2mpa01_regmap_config ; 
 struct mfd_cell* s2mps11_devs ; 
 struct regmap_config s2mps11_regmap_config ; 
 struct mfd_cell* s2mps13_devs ; 
 struct regmap_config s2mps13_regmap_config ; 
 struct mfd_cell* s2mps14_devs ; 
 struct regmap_config s2mps14_regmap_config ; 
 struct mfd_cell* s2mps15_devs ; 
 struct regmap_config s2mps15_regmap_config ; 
 struct mfd_cell* s2mpu02_devs ; 
 struct regmap_config s2mpu02_regmap_config ; 
 struct mfd_cell* s5m8751_devs ; 
 struct mfd_cell* s5m8763_devs ; 
 struct regmap_config s5m8763_regmap_config ; 
 struct mfd_cell* s5m8767_devs ; 
 struct regmap_config s5m8767_regmap_config ; 
 unsigned long sec_i2c_get_driver_data (struct i2c_client*,struct i2c_device_id const*) ; 
 int /*<<< orphan*/  sec_irq_init (struct sec_pmic_dev*) ; 
 int /*<<< orphan*/  sec_pmic_configure (struct sec_pmic_dev*) ; 
 int /*<<< orphan*/  sec_pmic_dump_rev (struct sec_pmic_dev*) ; 
 struct sec_platform_data* sec_pmic_i2c_parse_dt_pdata (TYPE_1__*) ; 
 struct regmap_config sec_regmap_config ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static int sec_pmic_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct sec_platform_data *pdata = dev_get_platdata(&i2c->dev);
	const struct regmap_config *regmap;
	const struct mfd_cell *sec_devs;
	struct sec_pmic_dev *sec_pmic;
	unsigned long device_type;
	int ret, num_sec_devs;

	sec_pmic = devm_kzalloc(&i2c->dev, sizeof(struct sec_pmic_dev),
				GFP_KERNEL);
	if (sec_pmic == NULL)
		return -ENOMEM;

	i2c_set_clientdata(i2c, sec_pmic);
	sec_pmic->dev = &i2c->dev;
	sec_pmic->i2c = i2c;
	sec_pmic->irq = i2c->irq;
	device_type = sec_i2c_get_driver_data(i2c, id);

	if (sec_pmic->dev->of_node) {
		pdata = sec_pmic_i2c_parse_dt_pdata(sec_pmic->dev);
		if (IS_ERR(pdata)) {
			ret = PTR_ERR(pdata);
			return ret;
		}
		pdata->device_type = device_type;
	}
	if (pdata) {
		sec_pmic->device_type = pdata->device_type;
		sec_pmic->irq_base = pdata->irq_base;
		sec_pmic->wakeup = pdata->wakeup;
		sec_pmic->pdata = pdata;
	}

	switch (sec_pmic->device_type) {
	case S2MPA01:
		regmap = &s2mpa01_regmap_config;
		break;
	case S2MPS11X:
		regmap = &s2mps11_regmap_config;
		break;
	case S2MPS13X:
		regmap = &s2mps13_regmap_config;
		break;
	case S2MPS14X:
		regmap = &s2mps14_regmap_config;
		break;
	case S2MPS15X:
		regmap = &s2mps15_regmap_config;
		break;
	case S5M8763X:
		regmap = &s5m8763_regmap_config;
		break;
	case S5M8767X:
		regmap = &s5m8767_regmap_config;
		break;
	case S2MPU02:
		regmap = &s2mpu02_regmap_config;
		break;
	default:
		regmap = &sec_regmap_config;
		break;
	}

	sec_pmic->regmap_pmic = devm_regmap_init_i2c(i2c, regmap);
	if (IS_ERR(sec_pmic->regmap_pmic)) {
		ret = PTR_ERR(sec_pmic->regmap_pmic);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	if (pdata && pdata->cfg_pmic_irq)
		pdata->cfg_pmic_irq();

	sec_irq_init(sec_pmic);

	pm_runtime_set_active(sec_pmic->dev);

	switch (sec_pmic->device_type) {
	case S5M8751X:
		sec_devs = s5m8751_devs;
		num_sec_devs = ARRAY_SIZE(s5m8751_devs);
		break;
	case S5M8763X:
		sec_devs = s5m8763_devs;
		num_sec_devs = ARRAY_SIZE(s5m8763_devs);
		break;
	case S5M8767X:
		sec_devs = s5m8767_devs;
		num_sec_devs = ARRAY_SIZE(s5m8767_devs);
		break;
	case S2MPA01:
		sec_devs = s2mpa01_devs;
		num_sec_devs = ARRAY_SIZE(s2mpa01_devs);
		break;
	case S2MPS11X:
		sec_devs = s2mps11_devs;
		num_sec_devs = ARRAY_SIZE(s2mps11_devs);
		break;
	case S2MPS13X:
		sec_devs = s2mps13_devs;
		num_sec_devs = ARRAY_SIZE(s2mps13_devs);
		break;
	case S2MPS14X:
		sec_devs = s2mps14_devs;
		num_sec_devs = ARRAY_SIZE(s2mps14_devs);
		break;
	case S2MPS15X:
		sec_devs = s2mps15_devs;
		num_sec_devs = ARRAY_SIZE(s2mps15_devs);
		break;
	case S2MPU02:
		sec_devs = s2mpu02_devs;
		num_sec_devs = ARRAY_SIZE(s2mpu02_devs);
		break;
	default:
		dev_err(&i2c->dev, "Unsupported device type (%lu)\n",
			sec_pmic->device_type);
		return -ENODEV;
	}
	ret = devm_mfd_add_devices(sec_pmic->dev, -1, sec_devs, num_sec_devs,
				   NULL, 0, NULL);
	if (ret)
		return ret;

	device_init_wakeup(sec_pmic->dev, sec_pmic->wakeup);
	sec_pmic_configure(sec_pmic);
	sec_pmic_dump_rev(sec_pmic);

	return ret;
}