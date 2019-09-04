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
struct dispc_device {TYPE_1__* feat; } ;
struct TYPE_2__ {int has_writeback; } ;

/* Variables and functions */

__attribute__((used)) static bool dispc_has_writeback(struct dispc_device *dispc)
{
	return dispc->feat->has_writeback;
}