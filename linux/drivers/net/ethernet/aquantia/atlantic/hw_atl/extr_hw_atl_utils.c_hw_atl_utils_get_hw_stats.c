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
struct aq_stats_s {int dummy; } ;
struct aq_hw_s {struct aq_stats_s curr_stats; } ;

/* Variables and functions */

struct aq_stats_s *hw_atl_utils_get_hw_stats(struct aq_hw_s *self)
{
	return &self->curr_stats;
}