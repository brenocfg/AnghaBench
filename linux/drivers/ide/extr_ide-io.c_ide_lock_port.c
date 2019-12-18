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
struct TYPE_3__ {int busy; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */

__attribute__((used)) static inline int ide_lock_port(ide_hwif_t *hwif)
{
	if (hwif->busy)
		return 1;

	hwif->busy = 1;

	return 0;
}