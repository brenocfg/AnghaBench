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
struct TYPE_2__ {scalar_t__ version; } ;
union ep_buffer_info {TYPE_1__ common; } ;
typedef  scalar_t__ u32 ;
struct epbuf_handler {union ep_buffer_info* info; } ;

/* Variables and functions */

bool fjes_hw_check_epbuf_version(struct epbuf_handler *epbh, u32 version)
{
	union ep_buffer_info *info = epbh->info;

	return (info->common.version == version);
}