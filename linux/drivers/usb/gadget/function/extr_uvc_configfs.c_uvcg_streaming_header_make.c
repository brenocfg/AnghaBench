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
struct TYPE_2__ {int bTerminalLink; int /*<<< orphan*/  bControlSize; int /*<<< orphan*/  bDescriptorSubType; int /*<<< orphan*/  bDescriptorType; } ;
struct uvcg_streaming_header {struct config_item item; TYPE_1__ desc; int /*<<< orphan*/  formats; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct config_item* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_DT_CS_INTERFACE ; 
 int /*<<< orphan*/  UVCG_STREAMING_CONTROL_SIZE ; 
 int /*<<< orphan*/  UVC_VS_INPUT_HEADER ; 
 int /*<<< orphan*/  config_item_init_type_name (struct config_item*,char const*,int /*<<< orphan*/ *) ; 
 struct uvcg_streaming_header* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvcg_streaming_header_type ; 

__attribute__((used)) static struct config_item
*uvcg_streaming_header_make(struct config_group *group, const char *name)
{
	struct uvcg_streaming_header *h;

	h = kzalloc(sizeof(*h), GFP_KERNEL);
	if (!h)
		return ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&h->formats);
	h->desc.bDescriptorType		= USB_DT_CS_INTERFACE;
	h->desc.bDescriptorSubType	= UVC_VS_INPUT_HEADER;
	h->desc.bTerminalLink		= 3;
	h->desc.bControlSize		= UVCG_STREAMING_CONTROL_SIZE;

	config_item_init_type_name(&h->item, name, &uvcg_streaming_header_type);

	return &h->item;
}