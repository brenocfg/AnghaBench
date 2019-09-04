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
struct blkfront_info {scalar_t__ feature_flush; scalar_t__ feature_fua; } ;

/* Variables and functions */

__attribute__((used)) static const char *flush_info(struct blkfront_info *info)
{
	if (info->feature_flush && info->feature_fua)
		return "barrier: enabled;";
	else if (info->feature_flush)
		return "flush diskcache: enabled;";
	else
		return "barrier or flush: disabled;";
}