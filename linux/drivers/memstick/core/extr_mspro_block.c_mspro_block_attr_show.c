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
typedef  int /*<<< orphan*/  sysfs_show_t ;

/* Variables and functions */
#define  MSPRO_BLOCK_ID_DEVINFO 133 
#define  MSPRO_BLOCK_ID_MBR 132 
#define  MSPRO_BLOCK_ID_MODELNAME 131 
#define  MSPRO_BLOCK_ID_SPECFILEVALUES1 130 
#define  MSPRO_BLOCK_ID_SPECFILEVALUES2 129 
#define  MSPRO_BLOCK_ID_SYSINFO 128 
 int /*<<< orphan*/  mspro_block_attr_show_default ; 
 int /*<<< orphan*/  mspro_block_attr_show_devinfo ; 
 int /*<<< orphan*/  mspro_block_attr_show_mbr ; 
 int /*<<< orphan*/  mspro_block_attr_show_modelname ; 
 int /*<<< orphan*/  mspro_block_attr_show_specfile ; 
 int /*<<< orphan*/  mspro_block_attr_show_sysinfo ; 

__attribute__((used)) static sysfs_show_t mspro_block_attr_show(unsigned char tag)
{
	switch (tag) {
	case MSPRO_BLOCK_ID_SYSINFO:
		return mspro_block_attr_show_sysinfo;
	case MSPRO_BLOCK_ID_MODELNAME:
		return mspro_block_attr_show_modelname;
	case MSPRO_BLOCK_ID_MBR:
		return mspro_block_attr_show_mbr;
	case MSPRO_BLOCK_ID_SPECFILEVALUES1:
	case MSPRO_BLOCK_ID_SPECFILEVALUES2:
		return mspro_block_attr_show_specfile;
	case MSPRO_BLOCK_ID_DEVINFO:
		return mspro_block_attr_show_devinfo;
	default:
		return mspro_block_attr_show_default;
	}
}