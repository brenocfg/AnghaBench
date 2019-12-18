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
struct wmi_device {int /*<<< orphan*/  dev; } ;
struct huawei_wmi_priv {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct huawei_wmi_priv*) ; 
 struct huawei_wmi_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int huawei_wmi_input_setup (struct wmi_device*) ; 
 int huawei_wmi_leds_setup (struct wmi_device*) ; 

__attribute__((used)) static int huawei_wmi_probe(struct wmi_device *wdev, const void *context)
{
	struct huawei_wmi_priv *priv;
	int err;

	priv = devm_kzalloc(&wdev->dev, sizeof(struct huawei_wmi_priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	dev_set_drvdata(&wdev->dev, priv);

	err = huawei_wmi_input_setup(wdev);
	if (err)
		return err;

	return huawei_wmi_leds_setup(wdev);
}