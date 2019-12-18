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
struct pqi_config_table_firmware_features {int* features_supported; int /*<<< orphan*/  num_elements; } ;

/* Variables and functions */
 unsigned int BITS_PER_BYTE ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool pqi_is_firmware_feature_supported(
	struct pqi_config_table_firmware_features *firmware_features,
	unsigned int bit_position)
{
	unsigned int byte_index;

	byte_index = bit_position / BITS_PER_BYTE;

	if (byte_index >= le16_to_cpu(firmware_features->num_elements))
		return false;

	return firmware_features->features_supported[byte_index] &
		(1 << (bit_position % BITS_PER_BYTE)) ? true : false;
}