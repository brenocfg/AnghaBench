#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ trans_type; } ;
struct usnic_ib_create_qp_cmd {TYPE_1__ spec; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ USNIC_TRANSPORT_MAX ; 
 scalar_t__ USNIC_TRANSPORT_UNKNOWN ; 

__attribute__((used)) static int create_qp_validate_user_data(struct usnic_ib_create_qp_cmd cmd)
{
	if (cmd.spec.trans_type <= USNIC_TRANSPORT_UNKNOWN ||
			cmd.spec.trans_type >= USNIC_TRANSPORT_MAX)
		return -EINVAL;

	return 0;
}