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
struct hd_geometry {int dummy; } ;
struct mapped_device {struct hd_geometry geometry; } ;

/* Variables and functions */

int dm_get_geometry(struct mapped_device *md, struct hd_geometry *geo)
{
	*geo = md->geometry;

	return 0;
}