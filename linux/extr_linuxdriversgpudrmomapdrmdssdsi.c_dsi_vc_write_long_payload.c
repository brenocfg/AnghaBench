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
typedef  int u8 ;
typedef  int u32 ;
struct dsi_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_VC_LONG_PACKET_PAYLOAD (int) ; 
 int /*<<< orphan*/  dsi_write_reg (struct dsi_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void dsi_vc_write_long_payload(struct dsi_data *dsi, int channel,
					     u8 b1, u8 b2, u8 b3, u8 b4)
{
	u32 val;

	val = b4 << 24 | b3 << 16 | b2 << 8  | b1 << 0;

/*	DSSDBG("\twriting %02x, %02x, %02x, %02x (%#010x)\n",
			b1, b2, b3, b4, val); */

	dsi_write_reg(dsi, DSI_VC_LONG_PACKET_PAYLOAD(channel), val);
}