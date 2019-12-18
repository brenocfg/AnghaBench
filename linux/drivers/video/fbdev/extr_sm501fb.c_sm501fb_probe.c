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
struct sm501fb_info {int /*<<< orphan*/ ** fb; int /*<<< orphan*/ * pdata; scalar_t__ edid_data; struct device* dev; } ;
struct sm501_platdata {int /*<<< orphan*/ * fb; } ;
struct device {TYPE_1__* parent; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; struct sm501_platdata* platform_data; } ;

/* Variables and functions */
 int EDID_LENGTH ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t HEAD_CRT ; 
 size_t HEAD_PANEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  driver_name_crt ; 
 int /*<<< orphan*/  driver_name_pnl ; 
 int /*<<< orphan*/  fb_mode ; 
 int /*<<< orphan*/  framebuffer_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct sm501fb_info*) ; 
 scalar_t__ kmemdup (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 struct sm501fb_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* of_get_property (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sm501fb_info*) ; 
 int /*<<< orphan*/  sm501_free_init_fb (struct sm501fb_info*,size_t) ; 
 int /*<<< orphan*/  sm501fb_def_pdata ; 
 int sm501fb_probe_one (struct sm501fb_info*,size_t) ; 
 int sm501fb_start (struct sm501fb_info*,struct platform_device*) ; 
 int sm501fb_start_one (struct sm501fb_info*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm501fb_stop (struct sm501fb_info*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  unregister_framebuffer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sm501fb_probe(struct platform_device *pdev)
{
	struct sm501fb_info *info;
	struct device *dev = &pdev->dev;
	int ret;

	/* allocate our framebuffers */
	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info) {
		dev_err(dev, "failed to allocate state\n");
		return -ENOMEM;
	}

	info->dev = dev = &pdev->dev;
	platform_set_drvdata(pdev, info);

	if (dev->parent->platform_data) {
		struct sm501_platdata *pd = dev->parent->platform_data;
		info->pdata = pd->fb;
	}

	if (info->pdata == NULL) {
		int found = 0;
#if defined(CONFIG_OF)
		struct device_node *np = pdev->dev.parent->of_node;
		const u8 *prop;
		const char *cp;
		int len;

		info->pdata = &sm501fb_def_pdata;
		if (np) {
			/* Get EDID */
			cp = of_get_property(np, "mode", &len);
			if (cp)
				strcpy(fb_mode, cp);
			prop = of_get_property(np, "edid", &len);
			if (prop && len == EDID_LENGTH) {
				info->edid_data = kmemdup(prop, EDID_LENGTH,
							  GFP_KERNEL);
				if (info->edid_data)
					found = 1;
			}
		}
#endif
		if (!found) {
			dev_info(dev, "using default configuration data\n");
			info->pdata = &sm501fb_def_pdata;
		}
	}

	/* probe for the presence of each panel */

	ret = sm501fb_probe_one(info, HEAD_CRT);
	if (ret < 0) {
		dev_err(dev, "failed to probe CRT\n");
		goto err_alloc;
	}

	ret = sm501fb_probe_one(info, HEAD_PANEL);
	if (ret < 0) {
		dev_err(dev, "failed to probe PANEL\n");
		goto err_probed_crt;
	}

	if (info->fb[HEAD_PANEL] == NULL &&
	    info->fb[HEAD_CRT] == NULL) {
		dev_err(dev, "no framebuffers found\n");
		ret = -ENODEV;
		goto err_alloc;
	}

	/* get the resources for both of the framebuffers */

	ret = sm501fb_start(info, pdev);
	if (ret) {
		dev_err(dev, "cannot initialise SM501\n");
		goto err_probed_panel;
	}

	ret = sm501fb_start_one(info, HEAD_CRT, driver_name_crt);
	if (ret) {
		dev_err(dev, "failed to start CRT\n");
		goto err_started;
	}

	ret = sm501fb_start_one(info, HEAD_PANEL, driver_name_pnl);
	if (ret) {
		dev_err(dev, "failed to start Panel\n");
		goto err_started_crt;
	}

	/* we registered, return ok */
	return 0;

err_started_crt:
	unregister_framebuffer(info->fb[HEAD_CRT]);
	sm501_free_init_fb(info, HEAD_CRT);

err_started:
	sm501fb_stop(info);

err_probed_panel:
	framebuffer_release(info->fb[HEAD_PANEL]);

err_probed_crt:
	framebuffer_release(info->fb[HEAD_CRT]);

err_alloc:
	kfree(info);

	return ret;
}