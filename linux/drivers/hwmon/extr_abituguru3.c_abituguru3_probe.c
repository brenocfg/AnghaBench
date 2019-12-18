#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct abituguru3_data {char* sysfs_names; TYPE_6__* sysfs_attr; int /*<<< orphan*/  hwmon_dev; TYPE_1__* sensors; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  addr; } ;
struct TYPE_16__ {int id; TYPE_1__* sensors; } ;
struct TYPE_11__ {char* name; } ;
struct TYPE_13__ {TYPE_2__ attr; } ;
struct TYPE_15__ {TYPE_4__ dev_attr; } ;
struct TYPE_14__ {int index; TYPE_4__ dev_attr; } ;
struct TYPE_12__ {int /*<<< orphan*/  start; } ;
struct TYPE_10__ {int type; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABIT_UGURU3_BOARD_ID ; 
 int ABIT_UGURU3_MAX_NO_SENSORS ; 
 int /*<<< orphan*/  ABIT_UGURU3_MISC_BANK ; 
 int ABIT_UGURU3_SYSFS_NAMES_LENGTH ; 
 int ARRAY_SIZE (TYPE_7__*) ; 
 int ENAMETOOLONG ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 TYPE_8__* abituguru3_motherboards ; 
 int abituguru3_read (struct abituguru3_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 TYPE_7__* abituguru3_sysfs_attr ; 
 TYPE_6__** abituguru3_sysfs_templ ; 
 int /*<<< orphan*/  abituguru3_update_device (int /*<<< orphan*/ *) ; 
 scalar_t__ device_create_file (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,TYPE_4__*) ; 
 struct abituguru3_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 unsigned int never_happen ; 
 TYPE_3__* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct abituguru3_data*) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int) ; 
 int /*<<< orphan*/  report_this ; 
 int snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int abituguru3_probe(struct platform_device *pdev)
{
	const int no_sysfs_attr[3] = { 10, 8, 7 };
	int sensor_index[3] = { 0, 1, 1 };
	struct abituguru3_data *data;
	int i, j, type, used, sysfs_names_free, sysfs_attr_i, res = -ENODEV;
	char *sysfs_filename;
	u8 buf[2];
	u16 id;

	data = devm_kzalloc(&pdev->dev, sizeof(struct abituguru3_data),
			    GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->addr = platform_get_resource(pdev, IORESOURCE_IO, 0)->start;
	mutex_init(&data->update_lock);
	platform_set_drvdata(pdev, data);

	/* Read the motherboard ID */
	i = abituguru3_read(data, ABIT_UGURU3_MISC_BANK, ABIT_UGURU3_BOARD_ID,
			    2, buf);
	if (i != 2)
		goto abituguru3_probe_error;

	/* Completely read the uGuru to see if one really is there */
	if (!abituguru3_update_device(&pdev->dev))
		goto abituguru3_probe_error;

	/* lookup the ID in our motherboard table */
	id = ((u16)buf[0] << 8) | (u16)buf[1];
	for (i = 0; abituguru3_motherboards[i].id; i++)
		if (abituguru3_motherboards[i].id == id)
			break;
	if (!abituguru3_motherboards[i].id) {
		pr_err("error unknown motherboard ID: %04X. %s\n",
		       (unsigned int)id, report_this);
		goto abituguru3_probe_error;
	}
	data->sensors = abituguru3_motherboards[i].sensors;

	pr_info("found Abit uGuru3, motherboard ID: %04X\n", (unsigned int)id);

	/* Fill the sysfs attr array */
	sysfs_attr_i = 0;
	sysfs_filename = data->sysfs_names;
	sysfs_names_free = ABIT_UGURU3_SYSFS_NAMES_LENGTH;
	for (i = 0; data->sensors[i].name; i++) {
		/* Fail safe check, this should never happen! */
		if (i >= ABIT_UGURU3_MAX_NO_SENSORS) {
			pr_err("Fatal error motherboard has more sensors then ABIT_UGURU3_MAX_NO_SENSORS. %s %s\n",
			       never_happen, report_this);
			res = -ENAMETOOLONG;
			goto abituguru3_probe_error;
		}
		type = data->sensors[i].type;
		for (j = 0; j < no_sysfs_attr[type]; j++) {
			used = snprintf(sysfs_filename, sysfs_names_free,
				abituguru3_sysfs_templ[type][j].dev_attr.attr.
				name, sensor_index[type]) + 1;
			data->sysfs_attr[sysfs_attr_i] =
				abituguru3_sysfs_templ[type][j];
			data->sysfs_attr[sysfs_attr_i].dev_attr.attr.name =
				sysfs_filename;
			data->sysfs_attr[sysfs_attr_i].index = i;
			sysfs_filename += used;
			sysfs_names_free -= used;
			sysfs_attr_i++;
		}
		sensor_index[type]++;
	}
	/* Fail safe check, this should never happen! */
	if (sysfs_names_free < 0) {
		pr_err("Fatal error ran out of space for sysfs attr names. %s %s\n",
		       never_happen, report_this);
		res = -ENAMETOOLONG;
		goto abituguru3_probe_error;
	}

	/* Register sysfs hooks */
	for (i = 0; i < sysfs_attr_i; i++)
		if (device_create_file(&pdev->dev,
				&data->sysfs_attr[i].dev_attr))
			goto abituguru3_probe_error;
	for (i = 0; i < ARRAY_SIZE(abituguru3_sysfs_attr); i++)
		if (device_create_file(&pdev->dev,
				&abituguru3_sysfs_attr[i].dev_attr))
			goto abituguru3_probe_error;

	data->hwmon_dev = hwmon_device_register(&pdev->dev);
	if (IS_ERR(data->hwmon_dev)) {
		res = PTR_ERR(data->hwmon_dev);
		goto abituguru3_probe_error;
	}

	return 0; /* success */

abituguru3_probe_error:
	for (i = 0; data->sysfs_attr[i].dev_attr.attr.name; i++)
		device_remove_file(&pdev->dev, &data->sysfs_attr[i].dev_attr);
	for (i = 0; i < ARRAY_SIZE(abituguru3_sysfs_attr); i++)
		device_remove_file(&pdev->dev,
			&abituguru3_sysfs_attr[i].dev_attr);
	return res;
}