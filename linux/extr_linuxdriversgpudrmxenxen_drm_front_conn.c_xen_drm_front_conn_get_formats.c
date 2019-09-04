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

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* plane_formats ; 

const u32 *xen_drm_front_conn_get_formats(int *format_count)
{
	*format_count = ARRAY_SIZE(plane_formats);
	return plane_formats;
}