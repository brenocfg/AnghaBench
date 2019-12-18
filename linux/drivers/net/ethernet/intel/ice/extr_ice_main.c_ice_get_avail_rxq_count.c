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
typedef  int /*<<< orphan*/  u16 ;
struct ice_pf {int /*<<< orphan*/  max_pf_rxqs; int /*<<< orphan*/  avail_q_mutex; int /*<<< orphan*/  avail_rxqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ice_get_avail_q_count (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

u16 ice_get_avail_rxq_count(struct ice_pf *pf)
{
	return ice_get_avail_q_count(pf->avail_rxqs, &pf->avail_q_mutex,
				     pf->max_pf_rxqs);
}