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
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_83xx_dump_template_hdr {int /*<<< orphan*/ * cap_sizes; } ;

/* Variables and functions */

inline u32 qlcnic_83xx_get_cap_size(void *t_hdr, int index)
{
	struct qlcnic_83xx_dump_template_hdr *hdr = t_hdr;

	return hdr->cap_sizes[index];
}