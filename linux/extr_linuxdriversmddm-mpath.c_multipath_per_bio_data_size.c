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
struct dm_mpath_io {int dummy; } ;
struct dm_bio_details {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static size_t multipath_per_bio_data_size(void)
{
	return sizeof(struct dm_mpath_io) + sizeof(struct dm_bio_details);
}