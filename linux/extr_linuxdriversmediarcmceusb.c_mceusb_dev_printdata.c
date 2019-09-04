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
typedef  int /*<<< orphan*/  u8 ;
struct mceusb_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void mceusb_dev_printdata(struct mceusb_dev *ir, u8 *buf, int buf_len,
				 int offset, int len, bool out)
{
#if defined(DEBUG) || defined(CONFIG_DYNAMIC_DEBUG)
	char *inout;
	u8 cmd, subcmd, *data;
	struct device *dev = ir->dev;
	int start, skip = 0;
	u32 carrier, period;

	/* skip meaningless 0xb1 0x60 header bytes on orig receiver */
	if (ir->flags.microsoft_gen1 && !out && !offset)
		skip = 2;

	if (len <= skip)
		return;

	dev_dbg(dev, "%cx data: %*ph (length=%d)",
		(out ? 't' : 'r'),
		min(len, buf_len - offset), buf + offset, len);

	inout = out ? "Request" : "Got";

	start  = offset + skip;
	cmd    = buf[start] & 0xff;
	subcmd = buf[start + 1] & 0xff;
	data = buf + start + 2;

	switch (cmd) {
	case MCE_CMD_NULL:
		if (subcmd == MCE_CMD_NULL)
			break;
		if ((subcmd == MCE_CMD_PORT_SYS) &&
		    (data[0] == MCE_CMD_RESUME))
			dev_dbg(dev, "Device resume requested");
		else
			dev_dbg(dev, "Unknown command 0x%02x 0x%02x",
				 cmd, subcmd);
		break;
	case MCE_CMD_PORT_SYS:
		switch (subcmd) {
		case MCE_RSP_EQEMVER:
			if (!out)
				dev_dbg(dev, "Emulator interface version %x",
					 data[0]);
			break;
		case MCE_CMD_G_REVISION:
			if (len == 2)
				dev_dbg(dev, "Get hw/sw rev?");
			else
				dev_dbg(dev, "hw/sw rev %*ph",
					4, &buf[start + 2]);
			break;
		case MCE_CMD_RESUME:
			dev_dbg(dev, "Device resume requested");
			break;
		case MCE_RSP_CMD_ILLEGAL:
			dev_dbg(dev, "Illegal PORT_SYS command");
			break;
		case MCE_RSP_EQWAKEVERSION:
			if (!out)
				dev_dbg(dev, "Wake version, proto: 0x%02x, payload: 0x%02x, address: 0x%02x, version: 0x%02x",
					data[0], data[1], data[2], data[3]);
			break;
		case MCE_RSP_GETPORTSTATUS:
			if (!out)
				/* We use data1 + 1 here, to match hw labels */
				dev_dbg(dev, "TX port %d: blaster is%s connected",
					 data[0] + 1, data[3] ? " not" : "");
			break;
		case MCE_CMD_FLASHLED:
			dev_dbg(dev, "Attempting to flash LED");
			break;
		default:
			dev_dbg(dev, "Unknown command 0x%02x 0x%02x",
				 cmd, subcmd);
			break;
		}
		break;
	case MCE_CMD_PORT_IR:
		switch (subcmd) {
		case MCE_CMD_SIG_END:
			dev_dbg(dev, "End of signal");
			break;
		case MCE_CMD_PING:
			dev_dbg(dev, "Ping");
			break;
		case MCE_CMD_UNKNOWN:
			dev_dbg(dev, "Resp to 9f 05 of 0x%02x 0x%02x",
				data[0], data[1]);
			break;
		case MCE_RSP_EQIRCFS:
			period = DIV_ROUND_CLOSEST((1U << data[0] * 2) *
						   (data[1] + 1), 10);
			if (!period)
				break;
			carrier = (1000 * 1000) / period;
			dev_dbg(dev, "%s carrier of %u Hz (period %uus)",
				 inout, carrier, period);
			break;
		case MCE_CMD_GETIRCFS:
			dev_dbg(dev, "Get carrier mode and freq");
			break;
		case MCE_RSP_EQIRTXPORTS:
			dev_dbg(dev, "%s transmit blaster mask of 0x%02x",
				 inout, data[0]);
			break;
		case MCE_RSP_EQIRTIMEOUT:
			/* value is in units of 50us, so x*50/1000 ms */
			period = ((data[0] << 8) | data[1]) *
				  MCE_TIME_UNIT / 1000;
			dev_dbg(dev, "%s receive timeout of %d ms",
				 inout, period);
			break;
		case MCE_CMD_GETIRTIMEOUT:
			dev_dbg(dev, "Get receive timeout");
			break;
		case MCE_CMD_GETIRTXPORTS:
			dev_dbg(dev, "Get transmit blaster mask");
			break;
		case MCE_RSP_EQIRRXPORTEN:
			dev_dbg(dev, "%s %s-range receive sensor in use",
				 inout, data[0] == 0x02 ? "short" : "long");
			break;
		case MCE_CMD_GETIRRXPORTEN:
		/* aka MCE_RSP_EQIRRXCFCNT */
			if (out)
				dev_dbg(dev, "Get receive sensor");
			else
				dev_dbg(dev, "RX carrier cycle count: %d",
					((data[0] << 8) | data[1]));
			break;
		case MCE_RSP_EQIRNUMPORTS:
			if (out)
				break;
			dev_dbg(dev, "Num TX ports: %x, num RX ports: %x",
				data[0], data[1]);
			break;
		case MCE_RSP_CMD_ILLEGAL:
			dev_dbg(dev, "Illegal PORT_IR command");
			break;
		default:
			dev_dbg(dev, "Unknown command 0x%02x 0x%02x",
				 cmd, subcmd);
			break;
		}
		break;
	default:
		break;
	}

	if (cmd == MCE_IRDATA_TRAILER)
		dev_dbg(dev, "End of raw IR data");
	else if ((cmd != MCE_CMD_PORT_IR) &&
		 ((cmd & MCE_PORT_MASK) == MCE_COMMAND_IRDATA))
		dev_dbg(dev, "Raw IR data, %d pulse/space samples", ir->rem);
#endif
}