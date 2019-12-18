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
struct queue_limits {scalar_t__ max_write_zeroes_sectors; } ;
struct mapped_device {int dummy; } ;

/* Variables and functions */
 struct queue_limits* dm_get_queue_limits (struct mapped_device*) ; 

void disable_write_zeroes(struct mapped_device *md)
{
	struct queue_limits *limits = dm_get_queue_limits(md);

	/* device doesn't really support WRITE ZEROES, disable it */
	limits->max_write_zeroes_sectors = 0;
}