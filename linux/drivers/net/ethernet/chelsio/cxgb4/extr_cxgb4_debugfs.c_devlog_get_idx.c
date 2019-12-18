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
struct devlog_info {scalar_t__ nentries; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */

__attribute__((used)) static inline void *devlog_get_idx(struct devlog_info *dinfo, loff_t pos)
{
	if (pos > dinfo->nentries)
		return NULL;

	return (void *)(uintptr_t)(pos + 1);
}