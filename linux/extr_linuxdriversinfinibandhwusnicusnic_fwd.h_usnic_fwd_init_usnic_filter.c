#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int flags; int proto_version; int /*<<< orphan*/  usnic_id; int /*<<< orphan*/  ethtype; } ;
struct TYPE_3__ {TYPE_2__ usnic; } ;
struct filter {TYPE_1__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IBOE ; 
 int FILTER_FIELD_USNIC_ETHTYPE ; 
 int FILTER_FIELD_USNIC_ID ; 
 int FILTER_FIELD_USNIC_PROTO ; 
 int /*<<< orphan*/  FILTER_USNIC_ID ; 
 int USNIC_PROTO_VER ; 
 int USNIC_ROCE_GRH_VER ; 
 int USNIC_ROCE_GRH_VER_SHIFT ; 

__attribute__((used)) static inline void usnic_fwd_init_usnic_filter(struct filter *filter,
						uint32_t usnic_id)
{
	filter->type = FILTER_USNIC_ID;
	filter->u.usnic.ethtype = ETH_P_IBOE;
	filter->u.usnic.flags = FILTER_FIELD_USNIC_ETHTYPE |
				FILTER_FIELD_USNIC_ID |
				FILTER_FIELD_USNIC_PROTO;
	filter->u.usnic.proto_version = (USNIC_ROCE_GRH_VER <<
					 USNIC_ROCE_GRH_VER_SHIFT) |
					 USNIC_PROTO_VER;
	filter->u.usnic.usnic_id = usnic_id;
}