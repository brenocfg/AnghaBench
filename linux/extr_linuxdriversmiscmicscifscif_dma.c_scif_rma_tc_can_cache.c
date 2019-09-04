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
struct scif_endpt {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool scif_rma_tc_can_cache(struct scif_endpt *ep, size_t cur_bytes)
{
	return false;
}