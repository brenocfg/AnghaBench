#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct esp {int scsi_id; int scsi_id_mask; TYPE_2__* host; int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {int this_id; } ;

/* Variables and functions */
 void* of_getintprop_default (struct device_node*,char*,int) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esp_get_scsi_id(struct esp *esp, struct platform_device *espdma)
{
	struct platform_device *op = to_platform_device(esp->dev);
	struct device_node *dp;

	dp = op->dev.of_node;
	esp->scsi_id = of_getintprop_default(dp, "initiator-id", 0xff);
	if (esp->scsi_id != 0xff)
		goto done;

	esp->scsi_id = of_getintprop_default(dp, "scsi-initiator-id", 0xff);
	if (esp->scsi_id != 0xff)
		goto done;

	esp->scsi_id = of_getintprop_default(espdma->dev.of_node,
					     "scsi-initiator-id", 7);

done:
	esp->host->this_id = esp->scsi_id;
	esp->scsi_id_mask = (1 << esp->scsi_id);
}