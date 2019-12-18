#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; TYPE_1__* id_entry; } ;
struct device_node {int dummy; } ;
struct atmel_nand_controller_caps {TYPE_2__* ops; int /*<<< orphan*/  has_dma; scalar_t__ legacy_of_bindings; } ;
struct TYPE_6__ {int (* probe ) (struct platform_device*,struct atmel_nand_controller_caps const*) ;} ;
struct TYPE_5__ {scalar_t__ driver_data; } ;

/* Variables and functions */
 int EINVAL ; 
 struct atmel_nand_controller_caps atmel_sam9261_nand_caps ; 
 struct atmel_nand_controller_caps atmel_sam9g45_nand_caps ; 
 struct atmel_nand_controller_caps atmel_sama5_nand_caps ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct atmel_nand_controller_caps* of_device_get_match_data (TYPE_3__*) ; 
 struct device_node* of_get_compatible_child (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int stub1 (struct platform_device*,struct atmel_nand_controller_caps const*) ; 

__attribute__((used)) static int atmel_nand_controller_probe(struct platform_device *pdev)
{
	const struct atmel_nand_controller_caps *caps;

	if (pdev->id_entry)
		caps = (void *)pdev->id_entry->driver_data;
	else
		caps = of_device_get_match_data(&pdev->dev);

	if (!caps) {
		dev_err(&pdev->dev, "Could not retrieve NFC caps\n");
		return -EINVAL;
	}

	if (caps->legacy_of_bindings) {
		struct device_node *nfc_node;
		u32 ale_offs = 21;

		/*
		 * If we are parsing legacy DT props and the DT contains a
		 * valid NFC node, forward the request to the sama5 logic.
		 */
		nfc_node = of_get_compatible_child(pdev->dev.of_node,
						   "atmel,sama5d3-nfc");
		if (nfc_node) {
			caps = &atmel_sama5_nand_caps;
			of_node_put(nfc_node);
		}

		/*
		 * Even if the compatible says we are dealing with an
		 * at91rm9200 controller, the atmel,nand-has-dma specify that
		 * this controller supports DMA, which means we are in fact
		 * dealing with an at91sam9g45+ controller.
		 */
		if (!caps->has_dma &&
		    of_property_read_bool(pdev->dev.of_node,
					  "atmel,nand-has-dma"))
			caps = &atmel_sam9g45_nand_caps;

		/*
		 * All SoCs except the at91sam9261 are assigning ALE to A21 and
		 * CLE to A22. If atmel,nand-addr-offset != 21 this means we're
		 * actually dealing with an at91sam9261 controller.
		 */
		of_property_read_u32(pdev->dev.of_node,
				     "atmel,nand-addr-offset", &ale_offs);
		if (ale_offs != 21)
			caps = &atmel_sam9261_nand_caps;
	}

	return caps->ops->probe(pdev, caps);
}