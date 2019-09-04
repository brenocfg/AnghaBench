#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_8__ {int bus_id; int device; int func; } ;
struct i40e_hw {int debug_mask; TYPE_4__ bus; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr_low; int /*<<< orphan*/  addr_high; } ;
struct TYPE_5__ {int /*<<< orphan*/  param1; int /*<<< orphan*/  param0; } ;
struct TYPE_7__ {TYPE_2__ external; TYPE_1__ internal; } ;
struct i40e_aq_desc {scalar_t__ opcode; scalar_t__ flags; scalar_t__ datalen; scalar_t__ retval; TYPE_3__ params; int /*<<< orphan*/  cookie_low; int /*<<< orphan*/  cookie_high; } ;
typedef  int /*<<< orphan*/  prefix ;
typedef  enum i40e_debug_mask { ____Placeholder_i40e_debug_mask } i40e_debug_mask ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  i40e_debug (struct i40e_hw*,int,char*,...) ; 
 scalar_t__ le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int) ; 

void i40evf_debug_aq(struct i40e_hw *hw, enum i40e_debug_mask mask, void *desc,
		   void *buffer, u16 buf_len)
{
	struct i40e_aq_desc *aq_desc = (struct i40e_aq_desc *)desc;
	u8 *buf = (u8 *)buffer;

	if ((!(mask & hw->debug_mask)) || (desc == NULL))
		return;

	i40e_debug(hw, mask,
		   "AQ CMD: opcode 0x%04X, flags 0x%04X, datalen 0x%04X, retval 0x%04X\n",
		   le16_to_cpu(aq_desc->opcode),
		   le16_to_cpu(aq_desc->flags),
		   le16_to_cpu(aq_desc->datalen),
		   le16_to_cpu(aq_desc->retval));
	i40e_debug(hw, mask, "\tcookie (h,l) 0x%08X 0x%08X\n",
		   le32_to_cpu(aq_desc->cookie_high),
		   le32_to_cpu(aq_desc->cookie_low));
	i40e_debug(hw, mask, "\tparam (0,1)  0x%08X 0x%08X\n",
		   le32_to_cpu(aq_desc->params.internal.param0),
		   le32_to_cpu(aq_desc->params.internal.param1));
	i40e_debug(hw, mask, "\taddr (h,l)   0x%08X 0x%08X\n",
		   le32_to_cpu(aq_desc->params.external.addr_high),
		   le32_to_cpu(aq_desc->params.external.addr_low));

	if ((buffer != NULL) && (aq_desc->datalen != 0)) {
		u16 len = le16_to_cpu(aq_desc->datalen);

		i40e_debug(hw, mask, "AQ CMD Buffer:\n");
		if (buf_len < len)
			len = buf_len;
		/* write the full 16-byte chunks */
		if (hw->debug_mask & mask) {
			char prefix[27];

			snprintf(prefix, sizeof(prefix),
				 "i40evf %02x:%02x.%x: \t0x",
				 hw->bus.bus_id,
				 hw->bus.device,
				 hw->bus.func);

			print_hex_dump(KERN_INFO, prefix, DUMP_PREFIX_OFFSET,
				       16, 1, buf, len, false);
		}
	}
}