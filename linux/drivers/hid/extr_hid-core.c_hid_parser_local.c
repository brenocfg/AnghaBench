#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int delimiter_depth; int delimiter_branch; unsigned int usage_minimum; unsigned int usage_index; } ;
struct hid_parser {TYPE_1__ local; TYPE_2__* device; } ;
struct hid_item {int tag; int /*<<< orphan*/  size; } ;
typedef  unsigned int __u32 ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  HID_LOCAL_ITEM_TAG_DELIMITER 131 
#define  HID_LOCAL_ITEM_TAG_USAGE 130 
#define  HID_LOCAL_ITEM_TAG_USAGE_MAXIMUM 129 
#define  HID_LOCAL_ITEM_TAG_USAGE_MINIMUM 128 
 unsigned int HID_MAX_USAGES ; 
 int /*<<< orphan*/  dbg_hid (char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int hid_add_usage (struct hid_parser*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  hid_warn (TYPE_2__*,char*) ; 
 unsigned int item_udata (struct hid_item*) ; 

__attribute__((used)) static int hid_parser_local(struct hid_parser *parser, struct hid_item *item)
{
	__u32 data;
	unsigned n;
	__u32 count;

	data = item_udata(item);

	switch (item->tag) {
	case HID_LOCAL_ITEM_TAG_DELIMITER:

		if (data) {
			/*
			 * We treat items before the first delimiter
			 * as global to all usage sets (branch 0).
			 * In the moment we process only these global
			 * items and the first delimiter set.
			 */
			if (parser->local.delimiter_depth != 0) {
				hid_err(parser->device, "nested delimiters\n");
				return -1;
			}
			parser->local.delimiter_depth++;
			parser->local.delimiter_branch++;
		} else {
			if (parser->local.delimiter_depth < 1) {
				hid_err(parser->device, "bogus close delimiter\n");
				return -1;
			}
			parser->local.delimiter_depth--;
		}
		return 0;

	case HID_LOCAL_ITEM_TAG_USAGE:

		if (parser->local.delimiter_branch > 1) {
			dbg_hid("alternative usage ignored\n");
			return 0;
		}

		return hid_add_usage(parser, data, item->size);

	case HID_LOCAL_ITEM_TAG_USAGE_MINIMUM:

		if (parser->local.delimiter_branch > 1) {
			dbg_hid("alternative usage ignored\n");
			return 0;
		}

		parser->local.usage_minimum = data;
		return 0;

	case HID_LOCAL_ITEM_TAG_USAGE_MAXIMUM:

		if (parser->local.delimiter_branch > 1) {
			dbg_hid("alternative usage ignored\n");
			return 0;
		}

		count = data - parser->local.usage_minimum;
		if (count + parser->local.usage_index >= HID_MAX_USAGES) {
			/*
			 * We do not warn if the name is not set, we are
			 * actually pre-scanning the device.
			 */
			if (dev_name(&parser->device->dev))
				hid_warn(parser->device,
					 "ignoring exceeding usage max\n");
			data = HID_MAX_USAGES - parser->local.usage_index +
				parser->local.usage_minimum - 1;
			if (data <= 0) {
				hid_err(parser->device,
					"no more usage index available\n");
				return -1;
			}
		}

		for (n = parser->local.usage_minimum; n <= data; n++)
			if (hid_add_usage(parser, n, item->size)) {
				dbg_hid("hid_add_usage failed\n");
				return -1;
			}
		return 0;

	default:

		dbg_hid("unknown local item tag 0x%x\n", item->tag);
		return 0;
	}
	return 0;
}