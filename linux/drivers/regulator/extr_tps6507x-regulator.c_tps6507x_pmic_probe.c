#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tps_info {char* name; int /*<<< orphan*/  table; int /*<<< orphan*/  table_len; int /*<<< orphan*/  defdcdc_default; } ;
struct tps6507x_reg_platform_data {int /*<<< orphan*/  defdcdc_default; } ;
struct tps6507x_pmic {TYPE_2__* desc; struct tps_info** info; struct tps6507x_dev* mfd; int /*<<< orphan*/  io_lock; } ;
struct tps6507x_dev {struct tps6507x_pmic* pmic; int /*<<< orphan*/  dev; } ;
struct tps6507x_board {struct regulator_init_data* tps6507x_pmic_init_data; } ;
struct regulator_init_data {struct tps6507x_reg_platform_data* driver_data; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {struct tps6507x_pmic* driver_data; struct regulator_init_data* init_data; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct platform_device {int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct TYPE_5__ {char* name; int id; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/ * ops; int /*<<< orphan*/  volt_table; int /*<<< orphan*/  n_voltages; int /*<<< orphan*/  of_parse_cb; void* regulators_node; void* of_match; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  REGULATOR_VOLTAGE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int TPS6507X_NUM_REGULATOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct tps6507x_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct tps6507x_board* dev_get_platdata (int /*<<< orphan*/ ) ; 
 struct tps6507x_pmic* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_1__*,TYPE_2__*,struct regulator_config*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 void* of_match_ptr (char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tps6507x_dev*) ; 
 int /*<<< orphan*/  tps6507x_pmic_of_parse_cb ; 
 int /*<<< orphan*/  tps6507x_pmic_ops ; 
 struct tps_info* tps6507x_pmic_regs ; 

__attribute__((used)) static int tps6507x_pmic_probe(struct platform_device *pdev)
{
	struct tps6507x_dev *tps6507x_dev = dev_get_drvdata(pdev->dev.parent);
	struct tps_info *info = &tps6507x_pmic_regs[0];
	struct regulator_config config = { };
	struct regulator_init_data *init_data = NULL;
	struct regulator_dev *rdev;
	struct tps6507x_pmic *tps;
	struct tps6507x_board *tps_board;
	int i;

	/**
	 * tps_board points to pmic related constants
	 * coming from the board-evm file.
	 */

	tps_board = dev_get_platdata(tps6507x_dev->dev);
	if (tps_board)
		init_data = tps_board->tps6507x_pmic_init_data;

	tps = devm_kzalloc(&pdev->dev, sizeof(*tps), GFP_KERNEL);
	if (!tps)
		return -ENOMEM;

	mutex_init(&tps->io_lock);

	/* common for all regulators */
	tps->mfd = tps6507x_dev;

	for (i = 0; i < TPS6507X_NUM_REGULATOR; i++, info++) {
		/* Register the regulators */
		tps->info[i] = info;
		if (init_data && init_data[i].driver_data) {
			struct tps6507x_reg_platform_data *data =
					init_data[i].driver_data;
			info->defdcdc_default = data->defdcdc_default;
		}

		tps->desc[i].name = info->name;
		tps->desc[i].of_match = of_match_ptr(info->name);
		tps->desc[i].regulators_node = of_match_ptr("regulators");
		tps->desc[i].of_parse_cb = tps6507x_pmic_of_parse_cb;
		tps->desc[i].id = i;
		tps->desc[i].n_voltages = info->table_len;
		tps->desc[i].volt_table = info->table;
		tps->desc[i].ops = &tps6507x_pmic_ops;
		tps->desc[i].type = REGULATOR_VOLTAGE;
		tps->desc[i].owner = THIS_MODULE;

		config.dev = tps6507x_dev->dev;
		config.init_data = init_data;
		config.driver_data = tps;

		rdev = devm_regulator_register(&pdev->dev, &tps->desc[i],
					       &config);
		if (IS_ERR(rdev)) {
			dev_err(tps6507x_dev->dev,
				"failed to register %s regulator\n",
				pdev->name);
			return PTR_ERR(rdev);
		}
	}

	tps6507x_dev->pmic = tps;
	platform_set_drvdata(pdev, tps6507x_dev);

	return 0;
}