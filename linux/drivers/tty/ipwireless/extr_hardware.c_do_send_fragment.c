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
struct ipw_hardware {unsigned int ll_mtu; scalar_t__ hw_version; int /*<<< orphan*/  lock; TYPE_1__* memory_info_regs; scalar_t__ base_port; scalar_t__ tx_ready; } ;
typedef  unsigned short __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  memreg_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned short DCR_TXDONE ; 
 scalar_t__ HW_VERSION_1 ; 
 scalar_t__ HW_VERSION_2 ; 
 scalar_t__ IODCR ; 
 scalar_t__ IODWR ; 
 int /*<<< orphan*/  MEMRX_RX ; 
 unsigned short cpu_to_le16 (unsigned short) ; 
 int /*<<< orphan*/  dump_data_bytes (char*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  end_write_timing (unsigned int) ; 
 scalar_t__ ipwireless_debug ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_timing () ; 
 int /*<<< orphan*/  swap_packet_bitfield_to_le (unsigned char*) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_send_fragment(struct ipw_hardware *hw, unsigned char *data,
			    unsigned length)
{
	unsigned i;
	unsigned long flags;

	start_timing();
	BUG_ON(length > hw->ll_mtu);

	if (ipwireless_debug)
		dump_data_bytes("send", data, length);

	spin_lock_irqsave(&hw->lock, flags);

	hw->tx_ready = 0;
	swap_packet_bitfield_to_le(data);

	if (hw->hw_version == HW_VERSION_1) {
		outw((unsigned short) length, hw->base_port + IODWR);

		for (i = 0; i < length; i += 2) {
			unsigned short d = data[i];
			__le16 raw_data;

			if (i + 1 < length)
				d |= data[i + 1] << 8;
			raw_data = cpu_to_le16(d);
			outw(raw_data, hw->base_port + IODWR);
		}

		outw(DCR_TXDONE, hw->base_port + IODCR);
	} else if (hw->hw_version == HW_VERSION_2) {
		outw((unsigned short) length, hw->base_port);

		for (i = 0; i < length; i += 2) {
			unsigned short d = data[i];
			__le16 raw_data;

			if (i + 1 < length)
				d |= data[i + 1] << 8;
			raw_data = cpu_to_le16(d);
			outw(raw_data, hw->base_port);
		}
		while ((i & 3) != 2) {
			outw((unsigned short) 0xDEAD, hw->base_port);
			i += 2;
		}
		writew(MEMRX_RX, &hw->memory_info_regs->memreg_rx);
	}

	spin_unlock_irqrestore(&hw->lock, flags);

	end_write_timing(length);
}