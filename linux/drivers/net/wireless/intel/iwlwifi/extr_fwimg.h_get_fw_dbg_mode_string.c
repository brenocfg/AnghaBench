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
#define  EXTERNAL_MODE 131 
#define  MARBH_MODE 130 
#define  MIPI_MODE 129 
#define  SMEM_MODE 128 

__attribute__((used)) static inline const char *get_fw_dbg_mode_string(int mode)
{
	switch (mode) {
	case SMEM_MODE:
		return "SMEM";
	case EXTERNAL_MODE:
		return "EXTERNAL_DRAM";
	case MARBH_MODE:
		return "MARBH";
	case MIPI_MODE:
		return "MIPI";
	default:
		return "UNKNOWN";
	}
}