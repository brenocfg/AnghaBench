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
struct extcon_dev {struct extcon_cable* cables; } ;
struct extcon_cable {int /*<<< orphan*/  disp_bits; int /*<<< orphan*/  jack_bits; int /*<<< orphan*/  chg_bits; int /*<<< orphan*/  usb_bits; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EXTCON_PROP_CHG_MIN ; 
 int /*<<< orphan*/  EXTCON_PROP_DISP_MIN ; 
 int /*<<< orphan*/  EXTCON_PROP_JACK_MIN ; 
 int /*<<< orphan*/  EXTCON_PROP_USB_MIN ; 
#define  EXTCON_TYPE_CHG 131 
#define  EXTCON_TYPE_DISP 130 
#define  EXTCON_TYPE_JACK 129 
#define  EXTCON_TYPE_USB 128 
 int get_extcon_type (unsigned int) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_extcon_property_capability(struct extcon_dev *edev,
				unsigned int id, int index,unsigned int prop)
{
	struct extcon_cable *cable;
	int type, ret;

	/* Check whether the property is supported or not. */
	type = get_extcon_type(prop);
	if (type < 0)
		return type;

	cable = &edev->cables[index];

	switch (type) {
	case EXTCON_TYPE_USB:
		ret = test_bit(prop - EXTCON_PROP_USB_MIN, cable->usb_bits);
		break;
	case EXTCON_TYPE_CHG:
		ret = test_bit(prop - EXTCON_PROP_CHG_MIN, cable->chg_bits);
		break;
	case EXTCON_TYPE_JACK:
		ret = test_bit(prop - EXTCON_PROP_JACK_MIN, cable->jack_bits);
		break;
	case EXTCON_TYPE_DISP:
		ret = test_bit(prop - EXTCON_PROP_DISP_MIN, cable->disp_bits);
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}