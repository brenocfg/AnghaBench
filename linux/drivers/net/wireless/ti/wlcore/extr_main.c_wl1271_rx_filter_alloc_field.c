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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wl12xx_rx_filter_field {int /*<<< orphan*/  pattern; void* len; void* flags; int /*<<< orphan*/  offset; } ;
struct wl12xx_rx_filter {size_t num_fields; struct wl12xx_rx_filter_field* fields; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t WL1271_RX_FILTER_MAX_FIELDS ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void* const*,void*) ; 
 int /*<<< orphan*/  wl1271_warning (char*) ; 

int wl1271_rx_filter_alloc_field(struct wl12xx_rx_filter *filter,
				 u16 offset, u8 flags,
				 const u8 *pattern, u8 len)
{
	struct wl12xx_rx_filter_field *field;

	if (filter->num_fields == WL1271_RX_FILTER_MAX_FIELDS) {
		wl1271_warning("Max fields per RX filter. can't alloc another");
		return -EINVAL;
	}

	field = &filter->fields[filter->num_fields];

	field->pattern = kzalloc(len, GFP_KERNEL);
	if (!field->pattern) {
		wl1271_warning("Failed to allocate RX filter pattern");
		return -ENOMEM;
	}

	filter->num_fields++;

	field->offset = cpu_to_le16(offset);
	field->flags = flags;
	field->len = len;
	memcpy(field->pattern, pattern, len);

	return 0;
}