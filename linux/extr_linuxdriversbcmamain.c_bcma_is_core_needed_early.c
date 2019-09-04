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
typedef  int u16 ;

/* Variables and functions */
#define  BCMA_CORE_NS_NAND 129 
#define  BCMA_CORE_NS_QSPI 128 

__attribute__((used)) static bool bcma_is_core_needed_early(u16 core_id)
{
	switch (core_id) {
	case BCMA_CORE_NS_NAND:
	case BCMA_CORE_NS_QSPI:
		return true;
	}

	return false;
}