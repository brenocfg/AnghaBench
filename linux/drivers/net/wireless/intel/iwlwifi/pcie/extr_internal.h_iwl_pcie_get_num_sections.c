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
struct fw_img {int num_sec; TYPE_1__* sec; } ;
struct TYPE_2__ {scalar_t__ offset; } ;

/* Variables and functions */
 scalar_t__ CPU1_CPU2_SEPARATOR_SECTION ; 
 scalar_t__ PAGING_SEPARATOR_SECTION ; 

__attribute__((used)) static inline int iwl_pcie_get_num_sections(const struct fw_img *fw,
					    int start)
{
	int i = 0;

	while (start < fw->num_sec &&
	       fw->sec[start].offset != CPU1_CPU2_SEPARATOR_SECTION &&
	       fw->sec[start].offset != PAGING_SEPARATOR_SECTION) {
		start++;
		i++;
	}

	return i;
}