#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  u64; } ;
typedef  TYPE_1__ cvmx_helper_link_info_t ;

/* Variables and functions */

__attribute__((used)) static inline cvmx_helper_link_info_t cvmx_helper_link_get(int ipd_port)
{
	cvmx_helper_link_info_t ret = { .u64 = 0 };

	return ret;
}