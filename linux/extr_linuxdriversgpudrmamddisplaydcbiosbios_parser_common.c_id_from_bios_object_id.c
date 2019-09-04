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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
#define  OBJECT_TYPE_CONNECTOR 131 
#define  OBJECT_TYPE_ENCODER 130 
#define  OBJECT_TYPE_GENERIC 129 
#define  OBJECT_TYPE_GPU 128 
 int /*<<< orphan*/  connector_id_from_bios_object_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encoder_id_from_bios_object_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_id_from_bios_object_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_id_from_bios_object_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t id_from_bios_object_id(enum object_type type,
	uint32_t bios_object_id)
{
	switch (type) {
	case OBJECT_TYPE_GPU:
		return gpu_id_from_bios_object_id(bios_object_id);
	case OBJECT_TYPE_ENCODER:
		return (uint32_t)encoder_id_from_bios_object_id(bios_object_id);
	case OBJECT_TYPE_CONNECTOR:
		return (uint32_t)connector_id_from_bios_object_id(
				bios_object_id);
	case OBJECT_TYPE_GENERIC:
		return generic_id_from_bios_object_id(bios_object_id);
	default:
		return 0;
	}
}