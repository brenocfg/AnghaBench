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
typedef  int /*<<< orphan*/  u64 ;
struct cfq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFQ_IOPS_MODE_GROUP_DELAY ; 
 int /*<<< orphan*/  CFQ_SLICE_MODE_GROUP_DELAY ; 
 int /*<<< orphan*/  iops_mode (struct cfq_data*) ; 

__attribute__((used)) static inline u64 cfq_get_cfqg_vdisktime_delay(struct cfq_data *cfqd)
{
	if (!iops_mode(cfqd))
		return CFQ_SLICE_MODE_GROUP_DELAY;
	else
		return CFQ_IOPS_MODE_GROUP_DELAY;
}