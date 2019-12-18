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
typedef  int u64 ;
struct i40e_rx_flow_userdef {int flex_word; int flex_offset; int flex_filter; } ;
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_3__ {scalar_t__ data; } ;
struct ethtool_rx_flow_spec {int flow_type; TYPE_2__ m_ext; TYPE_1__ h_ext; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int EINVAL ; 
 int FLOW_EXT ; 
 int /*<<< orphan*/  I40E_USERDEF_FLEX_FILTER ; 
 int I40E_USERDEF_FLEX_OFFSET ; 
 int I40E_USERDEF_FLEX_WORD ; 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 int i40e_check_mask (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct i40e_rx_flow_userdef*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i40e_parse_rx_flow_user_data(struct ethtool_rx_flow_spec *fsp,
					struct i40e_rx_flow_userdef *data)
{
	u64 value, mask;
	int valid;

	/* Zero memory first so it's always consistent. */
	memset(data, 0, sizeof(*data));

	if (!(fsp->flow_type & FLOW_EXT))
		return 0;

	value = be64_to_cpu(*((__be64 *)fsp->h_ext.data));
	mask = be64_to_cpu(*((__be64 *)fsp->m_ext.data));

#define I40E_USERDEF_FLEX_WORD		GENMASK_ULL(15, 0)
#define I40E_USERDEF_FLEX_OFFSET	GENMASK_ULL(31, 16)
#define I40E_USERDEF_FLEX_FILTER	GENMASK_ULL(31, 0)

	valid = i40e_check_mask(mask, I40E_USERDEF_FLEX_FILTER);
	if (valid < 0) {
		return -EINVAL;
	} else if (valid) {
		data->flex_word = value & I40E_USERDEF_FLEX_WORD;
		data->flex_offset =
			(value & I40E_USERDEF_FLEX_OFFSET) >> 16;
		data->flex_filter = true;
	}

	return 0;
}