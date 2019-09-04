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
struct diag204_x_cpu_info {int /*<<< orphan*/  online_time; } ;
typedef  enum diag204_format { ____Placeholder_diag204_format } diag204_format ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int DIAG204_INFO_SIMPLE ; 

__attribute__((used)) static inline __u64 cpu_info__online_time(enum diag204_format type, void *hdr)
{
	if (type == DIAG204_INFO_SIMPLE)
		return 0;	/* online_time not available in simple info */
	else /* DIAG204_INFO_EXT */
		return ((struct diag204_x_cpu_info *)hdr)->online_time;
}