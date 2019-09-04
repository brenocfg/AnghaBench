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
typedef  int u64 ;
struct cfq_group {int vfraction; } ;
struct cfq_data {int cfq_target_latency; } ;

/* Variables and functions */
 int CFQ_SERVICE_SHIFT ; 

__attribute__((used)) static inline u64
cfq_group_slice(struct cfq_data *cfqd, struct cfq_group *cfqg)
{
	return cfqd->cfq_target_latency * cfqg->vfraction >> CFQ_SERVICE_SHIFT;
}