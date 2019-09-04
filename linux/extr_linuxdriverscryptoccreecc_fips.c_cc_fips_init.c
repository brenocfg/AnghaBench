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
struct device {int dummy; } ;
struct cc_fips_handle {int /*<<< orphan*/  tasklet; } ;
struct cc_drvdata {scalar_t__ hw_rev; struct cc_fips_handle* fips_handle; } ;

/* Variables and functions */
 scalar_t__ CC_HW_REV_712 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cc_get_tee_fips_status (struct cc_drvdata*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct device* drvdata_to_dev (struct cc_drvdata*) ; 
 int /*<<< orphan*/  fips_dsr ; 
 struct cc_fips_handle* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tee_fips_error (struct device*) ; 

int cc_fips_init(struct cc_drvdata *p_drvdata)
{
	struct cc_fips_handle *fips_h;
	struct device *dev = drvdata_to_dev(p_drvdata);

	if (p_drvdata->hw_rev < CC_HW_REV_712)
		return 0;

	fips_h = kzalloc(sizeof(*fips_h), GFP_KERNEL);
	if (!fips_h)
		return -ENOMEM;

	p_drvdata->fips_handle = fips_h;

	dev_dbg(dev, "Initializing fips tasklet\n");
	tasklet_init(&fips_h->tasklet, fips_dsr, (unsigned long)p_drvdata);

	if (!cc_get_tee_fips_status(p_drvdata))
		tee_fips_error(dev);

	return 0;
}