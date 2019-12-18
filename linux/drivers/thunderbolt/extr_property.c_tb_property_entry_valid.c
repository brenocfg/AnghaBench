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
struct tb_property_entry {int type; size_t length; size_t value; } ;

/* Variables and functions */
#define  TB_PROPERTY_TYPE_DATA 131 
#define  TB_PROPERTY_TYPE_DIRECTORY 130 
#define  TB_PROPERTY_TYPE_TEXT 129 
#define  TB_PROPERTY_TYPE_VALUE 128 

__attribute__((used)) static bool tb_property_entry_valid(const struct tb_property_entry *entry,
				  size_t block_len)
{
	switch (entry->type) {
	case TB_PROPERTY_TYPE_DIRECTORY:
	case TB_PROPERTY_TYPE_DATA:
	case TB_PROPERTY_TYPE_TEXT:
		if (entry->length > block_len)
			return false;
		if (entry->value + entry->length > block_len)
			return false;
		break;

	case TB_PROPERTY_TYPE_VALUE:
		if (entry->length != 1)
			return false;
		break;
	}

	return true;
}