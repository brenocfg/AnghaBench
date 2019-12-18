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
typedef  int u8 ;
typedef  int u32 ;
struct dib9000_state {int fe_id; TYPE_2__** fe; } ;
struct TYPE_3__ {int frequency; int bandwidth_hz; scalar_t__ delivery_system; } ;
struct TYPE_4__ {TYPE_1__ dtv_property_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_MM_W_CHANNEL_HEAD ; 
 scalar_t__ SYS_DVBT ; 
 int /*<<< orphan*/  dib9000_risc_mem_write (struct dib9000_state*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void dib9000_fw_set_channel_head(struct dib9000_state *state)
{
	u8 b[9];
	u32 freq = state->fe[0]->dtv_property_cache.frequency / 1000;
	if (state->fe_id % 2)
		freq += 101;

	b[0] = (u8) ((freq >> 0) & 0xff);
	b[1] = (u8) ((freq >> 8) & 0xff);
	b[2] = (u8) ((freq >> 16) & 0xff);
	b[3] = (u8) ((freq >> 24) & 0xff);
	b[4] = (u8) ((state->fe[0]->dtv_property_cache.bandwidth_hz / 1000 >> 0) & 0xff);
	b[5] = (u8) ((state->fe[0]->dtv_property_cache.bandwidth_hz / 1000 >> 8) & 0xff);
	b[6] = (u8) ((state->fe[0]->dtv_property_cache.bandwidth_hz / 1000 >> 16) & 0xff);
	b[7] = (u8) ((state->fe[0]->dtv_property_cache.bandwidth_hz / 1000 >> 24) & 0xff);
	b[8] = 0x80;		/* do not wait for CELL ID when doing autosearch */
	if (state->fe[0]->dtv_property_cache.delivery_system == SYS_DVBT)
		b[8] |= 1;
	dib9000_risc_mem_write(state, FE_MM_W_CHANNEL_HEAD, b);
}