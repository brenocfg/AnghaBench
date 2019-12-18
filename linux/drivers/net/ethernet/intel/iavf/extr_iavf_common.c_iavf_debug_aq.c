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
struct iavf_hw {int debug_mask; TYPE_4__ bus; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr_low; int /*<<< orphan*/  addr_high; } ;
struct TYPE_5__ {int /*<<< orphan*/  param1; int /*<<< orphan*/  param0; } ;
struct TYPE_7__ {TYPE_2__ external; TYPE_1__ internal; } ;
struct iavf_aq_desc {scalar_t__ datalen; TYPE_3__ params; int /*<<< orphan*/  cookie_low; int /*<<< orphan*/  cookie_high; scalar_t__ retval; scalar_t__ flags; scalar_t__ opcode; } ;
typedef  int /*<<< orphan*/  prefix ;
typedef  enum iavf_debug_mask { ____Placeholder_iavf_debug_mask } iavf_debug_mask ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  iavf_debug (struct iavf_hw*,int,char*,...) ; 
 scalar_t__ le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int) ; 

void iavf_debug_aq(struct iavf_hw *hw, enum iavf_debug_mask mask, void *desc,
		   void *buffer, u16 buf_len)
{
	struct iavf_aq_desc *aq_desc = (struct iavf_aq_desc *)desc;
	u8 *buf = (u8 *)buffer;

	if ((!(mask & hw->debug_mask)) || !desc)
		return;

	iavf_debug(hw, mask,
		   "AQ CMD: opcode 0x%04X, flags 0x%04X, datalen 0x%04X, retval 0x%04X\n",
		   le16_to_cpu(aq_desc->opcode),
		   le16_to_cpu(aq_desc->flags),
		   le16_to_cpu(aq_desc->datalen),
		   le16_to_cpu(aq_desc->retval));
	iavf_debug(hw, mask, "\tcookie (h,l) 0x%08X 0x%08X\n",
		   le32_to_cpu(aq_desc->cookie_high),
		   le32_to_cpu(aq_desc->cookie_low));
	iavf_debug(hw, mask, "\tparam (0,1)  0x%08X 0x%08X\n",
		   le32_to_cpu(aq_desc->params.internal.param0),
		   le32_to_cpu(aq_desc->params.internal.param1));
	iavf_debug(hw, mask, "\taddr (h,l)   0x%08X 0x%08X\n",
		   le32_to_cpu(aq_desc->params.external.addr_high),
		   le32_to_cpu(aq_desc->params.external.addr_low));

	if (buffer && aq_desc->datalen) {
		u16 len = le16_to_cpu(aq_desc->datalen);

		iavf_debug(hw, mask, "AQ CMD Buffer:\n");
		if (buf_len < len)
			len = buf_len;
		/* write the full 16-byte chunks */
		if (hw->debug_mask & mask) {
			char prefix[27];

			snprintf(prefix, sizeof(prefix),
				 "iavf %02x:%02x.%x: \t0x",
				 hw->bus.bus_id,
				 hw->bus.device,
				 hw->bus.func);

			print_hex_dump(KERN_INFO, prefix, DUMP_PREFIX_OFFSET,
				       16, 1, buf, len, false);
		}
	}
}