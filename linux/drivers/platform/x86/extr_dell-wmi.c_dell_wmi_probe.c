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
struct dell_wmi_priv {int /*<<< orphan*/  interface_version; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dell_wmi_get_descriptor_valid () ; 
 int /*<<< orphan*/  dell_wmi_get_interface_version (int /*<<< orphan*/ *) ; 
 int dell_wmi_input_setup (struct wmi_device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct dell_wmi_priv*) ; 
 struct dell_wmi_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dell_wmi_probe(struct wmi_device *wdev, const void *context)
{
	struct dell_wmi_priv *priv;
	int ret;

	ret = dell_wmi_get_descriptor_valid();
	if (ret)
		return ret;

	priv = devm_kzalloc(
		&wdev->dev, sizeof(struct dell_wmi_priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	dev_set_drvdata(&wdev->dev, priv);

	if (!dell_wmi_get_interface_version(&priv->interface_version))
		return -EPROBE_DEFER;

	return dell_wmi_input_setup(wdev);
}