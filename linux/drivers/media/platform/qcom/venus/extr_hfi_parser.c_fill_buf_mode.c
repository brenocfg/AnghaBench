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
typedef  scalar_t__ u32 ;
struct venus_caps {int cap_bufs_mode_dynamic; } ;

/* Variables and functions */
 scalar_t__ const HFI_BUFFER_MODE_DYNAMIC ; 

__attribute__((used)) static void
fill_buf_mode(struct venus_caps *cap, const void *data, unsigned int num)
{
	const u32 *type = data;

	if (*type == HFI_BUFFER_MODE_DYNAMIC)
		cap->cap_bufs_mode_dynamic = true;
}