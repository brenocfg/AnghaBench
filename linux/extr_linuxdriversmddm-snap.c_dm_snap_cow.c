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
struct dm_snapshot {struct dm_dev* cow; } ;
struct dm_dev {int dummy; } ;

/* Variables and functions */

struct dm_dev *dm_snap_cow(struct dm_snapshot *s)
{
	return s->cow;
}