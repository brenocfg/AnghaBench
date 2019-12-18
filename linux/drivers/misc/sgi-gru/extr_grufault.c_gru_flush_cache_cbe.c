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
struct gru_control_block_extended {scalar_t__ cbrexecstatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  gru_flush_cache (struct gru_control_block_extended*) ; 
 scalar_t__ unlikely (struct gru_control_block_extended*) ; 

__attribute__((used)) static void gru_flush_cache_cbe(struct gru_control_block_extended *cbe)
{
	if (unlikely(cbe)) {
		cbe->cbrexecstatus = 0;         /* make CL dirty */
		gru_flush_cache(cbe);
	}
}