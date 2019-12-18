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
struct TYPE_2__ {char* card_name; int /*<<< orphan*/  dev; struct device* parent; int /*<<< orphan*/  simple_enable_set; int /*<<< orphan*/  enable_get; int /*<<< orphan*/  fieldbus_id_get; int /*<<< orphan*/  write_area; int /*<<< orphan*/  read_area; int /*<<< orphan*/  fieldbus_type; void* write_area_sz; void* read_area_sz; } ;
struct profi_priv {TYPE_1__ fbdev; struct anybuss_client* client; int /*<<< orphan*/  enable_lock; } ;
struct device {int dummy; } ;
struct anybuss_client {int /*<<< orphan*/  on_online_changed; int /*<<< orphan*/  on_area_updated; struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FIELDBUS_DEV_TYPE_PROFINET ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* PROFI_DPRAM_SIZE ; 
 int /*<<< orphan*/  anybuss_set_drvdata (struct anybuss_client*,struct profi_priv*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 struct profi_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int fieldbus_dev_register (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  profi_enable_get ; 
 int /*<<< orphan*/  profi_id_get ; 
 int /*<<< orphan*/  profi_on_area_updated ; 
 int /*<<< orphan*/  profi_on_online_changed ; 
 int /*<<< orphan*/  profi_read_area ; 
 int /*<<< orphan*/  profi_simple_enable ; 
 int /*<<< orphan*/  profi_write_area ; 

__attribute__((used)) static int profinet_probe(struct anybuss_client *client)
{
	struct profi_priv *priv;
	struct device *dev = &client->dev;
	int err;

	client->on_area_updated = profi_on_area_updated;
	client->on_online_changed = profi_on_online_changed;
	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	mutex_init(&priv->enable_lock);
	priv->client = client;
	priv->fbdev.read_area_sz = PROFI_DPRAM_SIZE;
	priv->fbdev.write_area_sz = PROFI_DPRAM_SIZE;
	priv->fbdev.card_name = "HMS Profinet IRT (Anybus-S)";
	priv->fbdev.fieldbus_type = FIELDBUS_DEV_TYPE_PROFINET;
	priv->fbdev.read_area = profi_read_area;
	priv->fbdev.write_area = profi_write_area;
	priv->fbdev.fieldbus_id_get = profi_id_get;
	priv->fbdev.enable_get = profi_enable_get;
	priv->fbdev.simple_enable_set = profi_simple_enable;
	priv->fbdev.parent = dev;
	err = fieldbus_dev_register(&priv->fbdev);
	if (err < 0)
		return err;
	dev_info(dev, "card detected, registered as %s",
		 dev_name(priv->fbdev.dev));
	anybuss_set_drvdata(client, priv);

	return 0;
}