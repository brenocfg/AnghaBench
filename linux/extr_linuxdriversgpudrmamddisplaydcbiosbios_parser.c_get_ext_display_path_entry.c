#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {TYPE_1__* sPath; } ;
struct TYPE_5__ {int /*<<< orphan*/  usDeviceConnector; } ;
typedef  TYPE_1__ EXT_DISPLAY_PATH ;
typedef  TYPE_2__ ATOM_EXTERNAL_DISPLAY_CONNECTION_INFO ;

/* Variables and functions */
 int ENUM_ID_MASK ; 
 int ENUM_ID_SHIFT ; 
 scalar_t__ INVALID_CONNECTOR ; 
 int MAX_NUMBER_OF_EXT_DISPLAY_PATH ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static EXT_DISPLAY_PATH *get_ext_display_path_entry(
	ATOM_EXTERNAL_DISPLAY_CONNECTION_INFO *config_table,
	uint32_t bios_object_id)
{
	EXT_DISPLAY_PATH *ext_display_path;
	uint32_t ext_display_path_index =
			((bios_object_id & ENUM_ID_MASK) >> ENUM_ID_SHIFT) - 1;

	if (ext_display_path_index >= MAX_NUMBER_OF_EXT_DISPLAY_PATH)
		return NULL;

	ext_display_path = &config_table->sPath[ext_display_path_index];

	if (le16_to_cpu(ext_display_path->usDeviceConnector) == INVALID_CONNECTOR)
		ext_display_path->usDeviceConnector = cpu_to_le16(0);

	return ext_display_path;
}