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
typedef  int u16 ;
struct tb_switch {int /*<<< orphan*/ * drom; TYPE_2__* tb; } ;
struct tb_drom_header {int data_len; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct device dev; } ;
struct TYPE_5__ {TYPE_1__* nhi; } ;
struct TYPE_4__ {TYPE_3__* pdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TB_DROM_DATA_START ; 
 int device_property_count_u8 (struct device*,char*) ; 
 int device_property_read_u8_array (struct device*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tb_drom_copy_efi(struct tb_switch *sw, u16 *size)
{
	struct device *dev = &sw->tb->nhi->pdev->dev;
	int len, res;

	len = device_property_count_u8(dev, "ThunderboltDROM");
	if (len < 0 || len < sizeof(struct tb_drom_header))
		return -EINVAL;

	sw->drom = kmalloc(len, GFP_KERNEL);
	if (!sw->drom)
		return -ENOMEM;

	res = device_property_read_u8_array(dev, "ThunderboltDROM", sw->drom,
									len);
	if (res)
		goto err;

	*size = ((struct tb_drom_header *)sw->drom)->data_len +
							  TB_DROM_DATA_START;
	if (*size > len)
		goto err;

	return 0;

err:
	kfree(sw->drom);
	sw->drom = NULL;
	return -EINVAL;
}