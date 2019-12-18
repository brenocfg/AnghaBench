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
struct manifest_desc {size_t size; char* data; int type; int /*<<< orphan*/  links; } ;
struct greybus_descriptor_string {int dummy; } ;
struct greybus_descriptor_interface {int dummy; } ;
struct greybus_descriptor_header {int type; int /*<<< orphan*/  size; } ;
struct greybus_descriptor_cport {int dummy; } ;
struct greybus_descriptor_bundle {int dummy; } ;
struct TYPE_2__ {size_t length; } ;
struct greybus_descriptor {TYPE_1__ string; struct greybus_descriptor_header header; } ;
struct gb_interface {int /*<<< orphan*/  manifest_descs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t ALIGN (size_t,int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  GREYBUS_TYPE_BUNDLE 132 
#define  GREYBUS_TYPE_CPORT 131 
#define  GREYBUS_TYPE_INTERFACE 130 
#define  GREYBUS_TYPE_INVALID 129 
#define  GREYBUS_TYPE_STRING 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  get_descriptor_type_string (int) ; 
 struct manifest_desc* kzalloc (int,int /*<<< orphan*/ ) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int identify_descriptor(struct gb_interface *intf,
			       struct greybus_descriptor *desc, size_t size)
{
	struct greybus_descriptor_header *desc_header = &desc->header;
	struct manifest_desc *descriptor;
	size_t desc_size;
	size_t expected_size;

	if (size < sizeof(*desc_header)) {
		dev_err(&intf->dev, "manifest too small (%zu < %zu)\n", size,
			sizeof(*desc_header));
		return -EINVAL;		/* Must at least have header */
	}

	desc_size = le16_to_cpu(desc_header->size);
	if (desc_size > size) {
		dev_err(&intf->dev, "descriptor too big (%zu > %zu)\n",
			desc_size, size);
		return -EINVAL;
	}

	/* Descriptor needs to at least have a header */
	expected_size = sizeof(*desc_header);

	switch (desc_header->type) {
	case GREYBUS_TYPE_STRING:
		expected_size += sizeof(struct greybus_descriptor_string);
		expected_size += desc->string.length;

		/* String descriptors are padded to 4 byte boundaries */
		expected_size = ALIGN(expected_size, 4);
		break;
	case GREYBUS_TYPE_INTERFACE:
		expected_size += sizeof(struct greybus_descriptor_interface);
		break;
	case GREYBUS_TYPE_BUNDLE:
		expected_size += sizeof(struct greybus_descriptor_bundle);
		break;
	case GREYBUS_TYPE_CPORT:
		expected_size += sizeof(struct greybus_descriptor_cport);
		break;
	case GREYBUS_TYPE_INVALID:
	default:
		dev_err(&intf->dev, "invalid descriptor type (%u)\n",
			desc_header->type);
		return -EINVAL;
	}

	if (desc_size < expected_size) {
		dev_err(&intf->dev, "%s descriptor too small (%zu < %zu)\n",
			get_descriptor_type_string(desc_header->type),
			desc_size, expected_size);
		return -EINVAL;
	}

	/* Descriptor bigger than what we expect */
	if (desc_size > expected_size) {
		dev_warn(&intf->dev, "%s descriptor size mismatch (want %zu got %zu)\n",
			 get_descriptor_type_string(desc_header->type),
			 expected_size, desc_size);
	}

	descriptor = kzalloc(sizeof(*descriptor), GFP_KERNEL);
	if (!descriptor)
		return -ENOMEM;

	descriptor->size = desc_size;
	descriptor->data = (char *)desc + sizeof(*desc_header);
	descriptor->type = desc_header->type;
	list_add_tail(&descriptor->links, &intf->manifest_descs);

	/* desc_size is positive and is known to fit in a signed int */

	return desc_size;
}