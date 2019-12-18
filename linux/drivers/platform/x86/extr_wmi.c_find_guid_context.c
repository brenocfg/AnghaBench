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
typedef  int /*<<< orphan*/  uuid_le ;
struct wmi_driver {struct wmi_device_id* id_table; } ;
struct wmi_device_id {void const* context; scalar_t__* guid_string; } ;
struct TYPE_2__ {int /*<<< orphan*/  guid; } ;
struct wmi_block {TYPE_1__ gblock; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ uuid_le_to_bin (scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const void *find_guid_context(struct wmi_block *wblock,
				      struct wmi_driver *wdriver)
{
	const struct wmi_device_id *id;
	uuid_le guid_input;

	if (wblock == NULL || wdriver == NULL)
		return NULL;
	if (wdriver->id_table == NULL)
		return NULL;

	id = wdriver->id_table;
	while (*id->guid_string) {
		if (uuid_le_to_bin(id->guid_string, &guid_input))
			continue;
		if (!memcmp(wblock->gblock.guid, &guid_input, 16))
			return id->context;
		id++;
	}
	return NULL;
}