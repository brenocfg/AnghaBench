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
struct cfq_data {int* cfq_slice; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFQ_SLICE_SCALE ; 
 unsigned short IOPRIO_BE_NR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int div_u64 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 cfq_prio_slice(struct cfq_data *cfqd, bool sync,
				 unsigned short prio)
{
	u64 base_slice = cfqd->cfq_slice[sync];
	u64 slice = div_u64(base_slice, CFQ_SLICE_SCALE);

	WARN_ON(prio >= IOPRIO_BE_NR);

	return base_slice + (slice * (4 - prio));
}