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
struct aq_rx_filter_l2 {scalar_t__ queue; int /*<<< orphan*/  location; int /*<<< orphan*/  user_priority; scalar_t__ user_priority_en; int /*<<< orphan*/  ethertype; } ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int aq_hw_err_from_flags (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_rpf_etht_flr_act_set (struct aq_hw_s*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_rpf_etht_flr_en_set (struct aq_hw_s*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_rpf_etht_flr_set (struct aq_hw_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_rpf_etht_rx_queue_en_set (struct aq_hw_s*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_rpf_etht_rx_queue_set (struct aq_hw_s*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_rpf_etht_user_priority_en_set (struct aq_hw_s*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_rpf_etht_user_priority_set (struct aq_hw_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_atl_b0_hw_fl2_set(struct aq_hw_s *self,
				struct aq_rx_filter_l2 *data)
{
	hw_atl_rpf_etht_flr_en_set(self, 1U, data->location);
	hw_atl_rpf_etht_flr_set(self, data->ethertype, data->location);
	hw_atl_rpf_etht_user_priority_en_set(self,
					     !!data->user_priority_en,
					     data->location);
	if (data->user_priority_en)
		hw_atl_rpf_etht_user_priority_set(self,
						  data->user_priority,
						  data->location);

	if (data->queue < 0) {
		hw_atl_rpf_etht_flr_act_set(self, 0U, data->location);
		hw_atl_rpf_etht_rx_queue_en_set(self, 0U, data->location);
	} else {
		hw_atl_rpf_etht_flr_act_set(self, 1U, data->location);
		hw_atl_rpf_etht_rx_queue_en_set(self, 1U, data->location);
		hw_atl_rpf_etht_rx_queue_set(self, data->queue, data->location);
	}

	return aq_hw_err_from_flags(self);
}