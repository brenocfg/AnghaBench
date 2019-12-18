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
typedef  size_t u32 ;
struct qlcnic_83xx_dump_template_hdr {size_t* saved_state; } ;

/* Variables and functions */

inline void qlcnic_83xx_set_saved_state(void *t_hdr, u32 index,
					u32 value)
{
	struct qlcnic_83xx_dump_template_hdr *hdr = t_hdr;

	hdr->saved_state[index] = value;
}