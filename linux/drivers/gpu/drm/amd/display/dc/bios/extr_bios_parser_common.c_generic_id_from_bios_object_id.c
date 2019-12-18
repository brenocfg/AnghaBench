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
typedef  int uint32_t ;
typedef  enum generic_id { ____Placeholder_generic_id } generic_id ;

/* Variables and functions */
 int GENERIC_ID_GLSYNC ; 
 int GENERIC_ID_MXM_OPM ; 
 int GENERIC_ID_STEREO ; 
 int GENERIC_ID_UNKNOWN ; 
#define  GENERIC_OBJECT_ID_GLSYNC 130 
#define  GENERIC_OBJECT_ID_MXM_OPM 129 
#define  GENERIC_OBJECT_ID_STEREO_PIN 128 
 int gpu_id_from_bios_object_id (int) ; 

__attribute__((used)) static enum generic_id generic_id_from_bios_object_id(uint32_t bios_object_id)
{
	uint32_t bios_generic_id = gpu_id_from_bios_object_id(bios_object_id);

	enum generic_id id;

	switch (bios_generic_id) {
	case GENERIC_OBJECT_ID_MXM_OPM:
		id = GENERIC_ID_MXM_OPM;
		break;
	case GENERIC_OBJECT_ID_GLSYNC:
		id = GENERIC_ID_GLSYNC;
		break;
	case GENERIC_OBJECT_ID_STEREO_PIN:
		id = GENERIC_ID_STEREO;
		break;
	default:
		id = GENERIC_ID_UNKNOWN;
		break;
	}

	return id;
}