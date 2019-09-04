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
struct mddev {scalar_t__ reshape_position; scalar_t__ layout; scalar_t__ new_layout; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ MaxSector ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 

__attribute__((used)) static ssize_t
layout_show(struct mddev *mddev, char *page)
{
	/* just a number, not meaningful for all levels */
	if (mddev->reshape_position != MaxSector &&
	    mddev->layout != mddev->new_layout)
		return sprintf(page, "%d (%d)\n",
			       mddev->new_layout, mddev->layout);
	return sprintf(page, "%d\n", mddev->layout);
}