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

/* Variables and functions */
#define  MSPRO_BLOCK_ID_DEVINFO 135 
#define  MSPRO_BLOCK_ID_MBR 134 
#define  MSPRO_BLOCK_ID_MODELNAME 133 
#define  MSPRO_BLOCK_ID_PBR16 132 
#define  MSPRO_BLOCK_ID_PBR32 131 
#define  MSPRO_BLOCK_ID_SPECFILEVALUES1 130 
#define  MSPRO_BLOCK_ID_SPECFILEVALUES2 129 
#define  MSPRO_BLOCK_ID_SYSINFO 128 

__attribute__((used)) static const char *mspro_block_attr_name(unsigned char tag)
{
	switch (tag) {
	case MSPRO_BLOCK_ID_SYSINFO:
		return "attr_sysinfo";
	case MSPRO_BLOCK_ID_MODELNAME:
		return "attr_modelname";
	case MSPRO_BLOCK_ID_MBR:
		return "attr_mbr";
	case MSPRO_BLOCK_ID_PBR16:
		return "attr_pbr16";
	case MSPRO_BLOCK_ID_PBR32:
		return "attr_pbr32";
	case MSPRO_BLOCK_ID_SPECFILEVALUES1:
		return "attr_specfilevalues1";
	case MSPRO_BLOCK_ID_SPECFILEVALUES2:
		return "attr_specfilevalues2";
	case MSPRO_BLOCK_ID_DEVINFO:
		return "attr_devinfo";
	default:
		return NULL;
	};
}