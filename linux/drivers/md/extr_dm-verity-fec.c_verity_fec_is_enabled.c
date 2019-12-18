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
struct dm_verity {TYPE_1__* fec; } ;
struct TYPE_2__ {scalar_t__ dev; } ;

/* Variables and functions */

bool verity_fec_is_enabled(struct dm_verity *v)
{
	return v->fec && v->fec->dev;
}