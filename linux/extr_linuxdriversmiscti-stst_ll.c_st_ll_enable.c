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
struct st_data_s {int /*<<< orphan*/  ll_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_LL_AWAKE ; 

void st_ll_enable(struct st_data_s *ll)
{
	ll->ll_state = ST_LL_AWAKE;
}