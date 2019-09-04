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
struct vas_tx_win_attr {scalar_t__ tc_mode; scalar_t__ wcreds_max; scalar_t__ rsvd_txbuf_count; scalar_t__ user_win; } ;
typedef  enum vas_cop_type { ____Placeholder_vas_cop_type } vas_cop_type ;

/* Variables and functions */
 int VAS_COP_TYPE_FTW ; 
 int VAS_COP_TYPE_MAX ; 
 scalar_t__ VAS_THRESH_DISABLED ; 
 scalar_t__ VAS_TX_WCREDS_MAX ; 

__attribute__((used)) static bool tx_win_args_valid(enum vas_cop_type cop,
			struct vas_tx_win_attr *attr)
{
	if (attr->tc_mode != VAS_THRESH_DISABLED)
		return false;

	if (cop > VAS_COP_TYPE_MAX)
		return false;

	if (attr->wcreds_max > VAS_TX_WCREDS_MAX)
		return false;

	if (attr->user_win &&
			(cop != VAS_COP_TYPE_FTW || attr->rsvd_txbuf_count))
		return false;

	return true;
}