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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct dsi_data {TYPE_1__* vc; } ;
struct TYPE_2__ {int vc_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_VC_LONG_PACKET_HEADER (int) ; 
 int FLD_VAL (int,int,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dsi_bus_is_locked (struct dsi_data*) ; 
 int /*<<< orphan*/  dsi_write_reg (struct dsi_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void dsi_vc_write_long_header(struct dsi_data *dsi, int channel,
					    u8 data_type, u16 len, u8 ecc)
{
	u32 val;
	u8 data_id;

	WARN_ON(!dsi_bus_is_locked(dsi));

	data_id = data_type | dsi->vc[channel].vc_id << 6;

	val = FLD_VAL(data_id, 7, 0) | FLD_VAL(len, 23, 8) |
		FLD_VAL(ecc, 31, 24);

	dsi_write_reg(dsi, DSI_VC_LONG_PACKET_HEADER(channel), val);
}