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
struct mapped_device {int type; } ;
typedef  enum dm_queue_mode { ____Placeholder_dm_queue_mode } dm_queue_mode ;

/* Variables and functions */

enum dm_queue_mode dm_get_md_type(struct mapped_device *md)
{
	return md->type;
}