#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  address; int /*<<< orphan*/  adapter_id; } ;
struct TYPE_5__ {TYPE_1__ i2c; } ;
struct TYPE_6__ {TYPE_2__ match; int /*<<< orphan*/  match_type; int /*<<< orphan*/  list; } ;
struct ceu_subdev {TYPE_3__ asd; int /*<<< orphan*/  mbus_flags; } ;
struct ceu_platform_data {unsigned int num_subdevs; struct ceu_async_subdev* subdevs; } ;
struct ceu_device {int /*<<< orphan*/  notifier; struct ceu_subdev* subdevs; } ;
struct ceu_async_subdev {int /*<<< orphan*/  i2c_address; int /*<<< orphan*/  i2c_adapter_id; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V4L2_ASYNC_MATCH_I2C ; 
 int ceu_init_async_subdevs (struct ceu_device*,unsigned int) ; 
 int v4l2_async_notifier_add_subdev (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ceu_parse_platform_data(struct ceu_device *ceudev,
				   const struct ceu_platform_data *pdata)
{
	const struct ceu_async_subdev *async_sd;
	struct ceu_subdev *ceu_sd;
	unsigned int i;
	int ret;

	if (pdata->num_subdevs == 0)
		return -ENODEV;

	ret = ceu_init_async_subdevs(ceudev, pdata->num_subdevs);
	if (ret)
		return ret;

	for (i = 0; i < pdata->num_subdevs; i++) {

		/* Setup the ceu subdevice and the async subdevice. */
		async_sd = &pdata->subdevs[i];
		ceu_sd = &ceudev->subdevs[i];

		INIT_LIST_HEAD(&ceu_sd->asd.list);

		ceu_sd->mbus_flags	= async_sd->flags;
		ceu_sd->asd.match_type	= V4L2_ASYNC_MATCH_I2C;
		ceu_sd->asd.match.i2c.adapter_id = async_sd->i2c_adapter_id;
		ceu_sd->asd.match.i2c.address = async_sd->i2c_address;

		ret = v4l2_async_notifier_add_subdev(&ceudev->notifier,
						     &ceu_sd->asd);
		if (ret) {
			v4l2_async_notifier_cleanup(&ceudev->notifier);
			return ret;
		}
	}

	return pdata->num_subdevs;
}