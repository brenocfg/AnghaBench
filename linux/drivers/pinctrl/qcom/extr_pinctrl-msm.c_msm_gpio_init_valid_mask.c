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
typedef  int /*<<< orphan*/  u16 ;
struct msm_pinctrl {int /*<<< orphan*/  dev; TYPE_1__* soc; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int* reserved_gpios; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bitmap_fill (unsigned long*,unsigned int) ; 
 int /*<<< orphan*/  bitmap_zero (unsigned long*,unsigned int) ; 
 int /*<<< orphan*/  clear_bit (int const,unsigned long*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int device_property_count_u16 (int /*<<< orphan*/ ,char*) ; 
 int device_property_read_u16_array (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned int) ; 
 struct msm_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int msm_gpio_init_valid_mask(struct gpio_chip *gc,
				    unsigned long *valid_mask,
				    unsigned int ngpios)
{
	struct msm_pinctrl *pctrl = gpiochip_get_data(gc);
	int ret;
	unsigned int len, i;
	const int *reserved = pctrl->soc->reserved_gpios;
	u16 *tmp;

	/* Driver provided reserved list overrides DT and ACPI */
	if (reserved) {
		bitmap_fill(valid_mask, ngpios);
		for (i = 0; reserved[i] >= 0; i++) {
			if (i >= ngpios || reserved[i] >= ngpios) {
				dev_err(pctrl->dev, "invalid list of reserved GPIOs\n");
				return -EINVAL;
			}
			clear_bit(reserved[i], valid_mask);
		}

		return 0;
	}

	/* The number of GPIOs in the ACPI tables */
	len = ret = device_property_count_u16(pctrl->dev, "gpios");
	if (ret < 0)
		return 0;

	if (ret > ngpios)
		return -EINVAL;

	tmp = kmalloc_array(len, sizeof(*tmp), GFP_KERNEL);
	if (!tmp)
		return -ENOMEM;

	ret = device_property_read_u16_array(pctrl->dev, "gpios", tmp, len);
	if (ret < 0) {
		dev_err(pctrl->dev, "could not read list of GPIOs\n");
		goto out;
	}

	bitmap_zero(valid_mask, ngpios);
	for (i = 0; i < len; i++)
		set_bit(tmp[i], valid_mask);

out:
	kfree(tmp);
	return ret;
}