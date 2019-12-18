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
struct qlcnic_82xx_dump_template_hdr {int /*<<< orphan*/ * sys_info; } ;

/* Variables and functions */

void qlcnic_82xx_set_sys_info(void *t_hdr, int idx, u32 value)
{
	struct qlcnic_82xx_dump_template_hdr *hdr = t_hdr;

	hdr->sys_info[idx] = value;
}