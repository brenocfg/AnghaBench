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
struct wm8350_platform_data {int dummy; } ;
struct wm8350 {int /*<<< orphan*/ * dev; int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct wm8350_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct wm8350* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct wm8350*) ; 
 int wm8350_device_init (struct wm8350*,int /*<<< orphan*/ ,struct wm8350_platform_data*) ; 
 int /*<<< orphan*/  wm8350_regmap ; 

__attribute__((used)) static int wm8350_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct wm8350 *wm8350;
	struct wm8350_platform_data *pdata = dev_get_platdata(&i2c->dev);
	int ret = 0;

	wm8350 = devm_kzalloc(&i2c->dev, sizeof(struct wm8350), GFP_KERNEL);
	if (wm8350 == NULL)
		return -ENOMEM;

	wm8350->regmap = devm_regmap_init_i2c(i2c, &wm8350_regmap);
	if (IS_ERR(wm8350->regmap)) {
		ret = PTR_ERR(wm8350->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	i2c_set_clientdata(i2c, wm8350);
	wm8350->dev = &i2c->dev;

	return wm8350_device_init(wm8350, i2c->irq, pdata);
}