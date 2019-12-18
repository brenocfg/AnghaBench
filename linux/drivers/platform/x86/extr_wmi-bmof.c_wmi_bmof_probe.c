#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  kobj; } ;
struct wmi_device {TYPE_7__ dev; } ;
struct TYPE_10__ {char* name; int mode; } ;
struct TYPE_13__ {int /*<<< orphan*/  size; int /*<<< orphan*/  read; TYPE_1__ attr; } ;
struct bmof_priv {TYPE_3__* bmofdata; TYPE_4__ bmof_bin_attr; } ;
struct TYPE_11__ {int /*<<< orphan*/  length; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_2__ buffer; } ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_BUFFER ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_7__*,struct bmof_priv*) ; 
 struct bmof_priv* devm_kzalloc (TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  read_bmof ; 
 int /*<<< orphan*/  sysfs_bin_attr_init (TYPE_4__*) ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_3__* wmidev_block_query (struct wmi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wmi_bmof_probe(struct wmi_device *wdev, const void *context)
{
	struct bmof_priv *priv;
	int ret;

	priv = devm_kzalloc(&wdev->dev, sizeof(struct bmof_priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	dev_set_drvdata(&wdev->dev, priv);

	priv->bmofdata = wmidev_block_query(wdev, 0);
	if (!priv->bmofdata) {
		dev_err(&wdev->dev, "failed to read Binary MOF\n");
		return -EIO;
	}

	if (priv->bmofdata->type != ACPI_TYPE_BUFFER) {
		dev_err(&wdev->dev, "Binary MOF is not a buffer\n");
		ret = -EIO;
		goto err_free;
	}

	sysfs_bin_attr_init(&priv->bmof_bin_attr);
	priv->bmof_bin_attr.attr.name = "bmof";
	priv->bmof_bin_attr.attr.mode = 0400;
	priv->bmof_bin_attr.read = read_bmof;
	priv->bmof_bin_attr.size = priv->bmofdata->buffer.length;

	ret = sysfs_create_bin_file(&wdev->dev.kobj, &priv->bmof_bin_attr);
	if (ret)
		goto err_free;

	return 0;

 err_free:
	kfree(priv->bmofdata);
	return ret;
}