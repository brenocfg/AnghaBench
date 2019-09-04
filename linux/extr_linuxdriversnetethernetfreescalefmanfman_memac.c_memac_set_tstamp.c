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
struct fman_mac {int dummy; } ;

/* Variables and functions */

int memac_set_tstamp(struct fman_mac *memac, bool enable)
{
	return 0; /* Always enabled. */
}