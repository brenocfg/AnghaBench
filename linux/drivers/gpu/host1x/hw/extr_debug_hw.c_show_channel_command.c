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
typedef  int u32 ;
struct output {int dummy; } ;

/* Variables and functions */
#define  HOST1X_OPCODE_EXTEND 141 
 unsigned int HOST1X_OPCODE_EXTEND_ACQUIRE_MLOCK ; 
 unsigned int HOST1X_OPCODE_EXTEND_RELEASE_MLOCK ; 
#define  HOST1X_OPCODE_GATHER 140 
#define  HOST1X_OPCODE_GATHER_W 139 
#define  HOST1X_OPCODE_IMM 138 
#define  HOST1X_OPCODE_INCR 137 
#define  HOST1X_OPCODE_INCR_W 136 
#define  HOST1X_OPCODE_MASK 135 
#define  HOST1X_OPCODE_NONINCR 134 
#define  HOST1X_OPCODE_NONINCR_W 133 
#define  HOST1X_OPCODE_RESTART 132 
#define  HOST1X_OPCODE_SETAPPID 131 
#define  HOST1X_OPCODE_SETCLASS 130 
#define  HOST1X_OPCODE_SETPYLD 129 
#define  HOST1X_OPCODE_SETSTRMID 128 
 int INVALID_PAYLOAD ; 
 int /*<<< orphan*/  host1x_debug_cont (struct output*,char*,...) ; 
 unsigned int hweight16 (unsigned int) ; 
 unsigned int hweight8 (unsigned int) ; 

__attribute__((used)) static unsigned int show_channel_command(struct output *o, u32 val,
					 u32 *payload)
{
	unsigned int mask, subop, num, opcode;

	opcode = val >> 28;

	switch (opcode) {
	case HOST1X_OPCODE_SETCLASS:
		mask = val & 0x3f;
		if (mask) {
			host1x_debug_cont(o, "SETCL(class=%03x, offset=%03x, mask=%02x, [",
					    val >> 6 & 0x3ff,
					    val >> 16 & 0xfff, mask);
			return hweight8(mask);
		}

		host1x_debug_cont(o, "SETCL(class=%03x)\n", val >> 6 & 0x3ff);
		return 0;

	case HOST1X_OPCODE_INCR:
		num = val & 0xffff;
		host1x_debug_cont(o, "INCR(offset=%03x, [",
				    val >> 16 & 0xfff);
		if (!num)
			host1x_debug_cont(o, "])\n");

		return num;

	case HOST1X_OPCODE_NONINCR:
		num = val & 0xffff;
		host1x_debug_cont(o, "NONINCR(offset=%03x, [",
				    val >> 16 & 0xfff);
		if (!num)
			host1x_debug_cont(o, "])\n");

		return num;

	case HOST1X_OPCODE_MASK:
		mask = val & 0xffff;
		host1x_debug_cont(o, "MASK(offset=%03x, mask=%03x, [",
				    val >> 16 & 0xfff, mask);
		if (!mask)
			host1x_debug_cont(o, "])\n");

		return hweight16(mask);

	case HOST1X_OPCODE_IMM:
		host1x_debug_cont(o, "IMM(offset=%03x, data=%03x)\n",
				    val >> 16 & 0xfff, val & 0xffff);
		return 0;

	case HOST1X_OPCODE_RESTART:
		host1x_debug_cont(o, "RESTART(offset=%08x)\n", val << 4);
		return 0;

	case HOST1X_OPCODE_GATHER:
		host1x_debug_cont(o, "GATHER(offset=%03x, insert=%d, type=%d, count=%04x, addr=[",
				    val >> 16 & 0xfff, val >> 15 & 0x1,
				    val >> 14 & 0x1, val & 0x3fff);
		return 1;

#if HOST1X_HW >= 6
	case HOST1X_OPCODE_SETSTRMID:
		host1x_debug_cont(o, "SETSTRMID(offset=%06x)\n",
				  val & 0x3fffff);
		return 0;

	case HOST1X_OPCODE_SETAPPID:
		host1x_debug_cont(o, "SETAPPID(appid=%02x)\n", val & 0xff);
		return 0;

	case HOST1X_OPCODE_SETPYLD:
		*payload = val & 0xffff;
		host1x_debug_cont(o, "SETPYLD(data=%04x)\n", *payload);
		return 0;

	case HOST1X_OPCODE_INCR_W:
	case HOST1X_OPCODE_NONINCR_W:
		host1x_debug_cont(o, "%s(offset=%06x, ",
				  opcode == HOST1X_OPCODE_INCR_W ?
					"INCR_W" : "NONINCR_W",
				  val & 0x3fffff);
		if (*payload == 0) {
			host1x_debug_cont(o, "[])\n");
			return 0;
		} else if (*payload == INVALID_PAYLOAD) {
			host1x_debug_cont(o, "unknown)\n");
			return 0;
		} else {
			host1x_debug_cont(o, "[");
			return *payload;
		}

	case HOST1X_OPCODE_GATHER_W:
		host1x_debug_cont(o, "GATHER_W(count=%04x, addr=[",
				  val & 0x3fff);
		return 2;
#endif

	case HOST1X_OPCODE_EXTEND:
		subop = val >> 24 & 0xf;
		if (subop == HOST1X_OPCODE_EXTEND_ACQUIRE_MLOCK)
			host1x_debug_cont(o, "ACQUIRE_MLOCK(index=%d)\n",
					    val & 0xff);
		else if (subop == HOST1X_OPCODE_EXTEND_RELEASE_MLOCK)
			host1x_debug_cont(o, "RELEASE_MLOCK(index=%d)\n",
					    val & 0xff);
		else
			host1x_debug_cont(o, "EXTEND_UNKNOWN(%08x)\n", val);
		return 0;

	default:
		host1x_debug_cont(o, "UNKNOWN\n");
		return 0;
	}
}