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
struct enclosure_device {int dummy; } ;
struct enclosure_component {int active; } ;
typedef  enum enclosure_component_setting { ____Placeholder_enclosure_component_setting } enclosure_component_setting ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
#define  ENCLOSURE_SETTING_DISABLED 129 
#define  ENCLOSURE_SETTING_ENABLED 128 
 int /*<<< orphan*/  init_device_slot_control (unsigned char*,struct enclosure_component*,unsigned char*) ; 
 unsigned char* ses_get_page2_descriptor (struct enclosure_device*,struct enclosure_component*) ; 
 int /*<<< orphan*/  ses_page2_supported (struct enclosure_device*) ; 
 int ses_set_page2_descriptor (struct enclosure_device*,struct enclosure_component*,unsigned char*) ; 

__attribute__((used)) static int ses_set_active(struct enclosure_device *edev,
			  struct enclosure_component *ecomp,
			  enum enclosure_component_setting val)
{
	unsigned char desc[4];
	unsigned char *desc_ptr;

	if (!ses_page2_supported(edev))
		return -EINVAL;

	desc_ptr = ses_get_page2_descriptor(edev, ecomp);

	if (!desc_ptr)
		return -EIO;

	init_device_slot_control(desc, ecomp, desc_ptr);

	switch (val) {
	case ENCLOSURE_SETTING_DISABLED:
		desc[2] &= 0x7f;
		ecomp->active = 0;
		break;
	case ENCLOSURE_SETTING_ENABLED:
		desc[2] |= 0x80;
		ecomp->active = 1;
		break;
	default:
		/* SES doesn't do the SGPIO blink settings */
		return -EINVAL;
	}
	return ses_set_page2_descriptor(edev, ecomp, desc);
}