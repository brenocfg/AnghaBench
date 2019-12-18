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
struct config_item {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dwClockFrequency; int /*<<< orphan*/  bcdUVC; int /*<<< orphan*/  bDescriptorSubType; int /*<<< orphan*/  bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct uvcg_control_header {struct config_item item; TYPE_1__ desc; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct config_item* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_DT_CS_INTERFACE ; 
 int /*<<< orphan*/  UVC_DT_HEADER_SIZE (int) ; 
 int /*<<< orphan*/  UVC_VC_HEADER ; 
 int /*<<< orphan*/  config_item_init_type_name (struct config_item*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 struct uvcg_control_header* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvcg_control_header_type ; 

__attribute__((used)) static struct config_item *uvcg_control_header_make(struct config_group *group,
						    const char *name)
{
	struct uvcg_control_header *h;

	h = kzalloc(sizeof(*h), GFP_KERNEL);
	if (!h)
		return ERR_PTR(-ENOMEM);

	h->desc.bLength			= UVC_DT_HEADER_SIZE(1);
	h->desc.bDescriptorType		= USB_DT_CS_INTERFACE;
	h->desc.bDescriptorSubType	= UVC_VC_HEADER;
	h->desc.bcdUVC			= cpu_to_le16(0x0100);
	h->desc.dwClockFrequency	= cpu_to_le32(48000000);

	config_item_init_type_name(&h->item, name, &uvcg_control_header_type);

	return &h->item;
}