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
typedef  int u32 ;
struct lb_port_stats {void* trunc3; void* trunc2; void* trunc1; void* trunc0; void* ovflow3; void* ovflow2; void* ovflow1; void* ovflow0; void* drop; void* frames_1519_max; void* frames_1024_1518; void* frames_512_1023; void* frames_256_511; void* frames_128_255; void* frames_65_127; void* frames_64; void* error_frames; void* ucast_frames; void* mcast_frames; void* bcast_frames; void* frames; void* octets; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPS_PORT_STAT_LB_PORT_1024B_1518B_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_LB_PORT_128B_255B_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_LB_PORT_1519B_MAX_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_LB_PORT_256B_511B_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_LB_PORT_512B_1023B_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_LB_PORT_64B_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_LB_PORT_65B_127B_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_LB_PORT_BCAST_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_LB_PORT_BYTES_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_LB_PORT_DROP_FRAMES_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_LB_PORT_ERROR_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_LB_PORT_FRAMES_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_LB_PORT_MCAST_L ; 
 int /*<<< orphan*/  MPS_PORT_STAT_LB_PORT_UCAST_L ; 
 int /*<<< orphan*/  MPS_STAT_RX_BG_0_LB_DROP_FRAME_L ; 
 int /*<<< orphan*/  MPS_STAT_RX_BG_0_LB_TRUNC_FRAME_L ; 
 int /*<<< orphan*/  MPS_STAT_RX_BG_1_LB_DROP_FRAME_L ; 
 int /*<<< orphan*/  MPS_STAT_RX_BG_1_LB_TRUNC_FRAME_L ; 
 int /*<<< orphan*/  MPS_STAT_RX_BG_2_LB_DROP_FRAME_L ; 
 int /*<<< orphan*/  MPS_STAT_RX_BG_2_LB_TRUNC_FRAME_L ; 
 int /*<<< orphan*/  MPS_STAT_RX_BG_3_LB_DROP_FRAME_L ; 
 int /*<<< orphan*/  MPS_STAT_RX_BG_3_LB_TRUNC_FRAME_L ; 
 int /*<<< orphan*/  PORT_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T5_PORT_REG (int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_t4 (int /*<<< orphan*/ ) ; 
 int t4_get_mps_bg_map (struct adapter*,int) ; 
 void* t4_read_reg64 (struct adapter*,int /*<<< orphan*/ ) ; 

void t4_get_lb_stats(struct adapter *adap, int idx, struct lb_port_stats *p)
{
	u32 bgmap = t4_get_mps_bg_map(adap, idx);

#define GET_STAT(name) \
	t4_read_reg64(adap, \
	(is_t4(adap->params.chip) ? \
	PORT_REG(idx, MPS_PORT_STAT_LB_PORT_##name##_L) : \
	T5_PORT_REG(idx, MPS_PORT_STAT_LB_PORT_##name##_L)))
#define GET_STAT_COM(name) t4_read_reg64(adap, MPS_STAT_##name##_L)

	p->octets           = GET_STAT(BYTES);
	p->frames           = GET_STAT(FRAMES);
	p->bcast_frames     = GET_STAT(BCAST);
	p->mcast_frames     = GET_STAT(MCAST);
	p->ucast_frames     = GET_STAT(UCAST);
	p->error_frames     = GET_STAT(ERROR);

	p->frames_64        = GET_STAT(64B);
	p->frames_65_127    = GET_STAT(65B_127B);
	p->frames_128_255   = GET_STAT(128B_255B);
	p->frames_256_511   = GET_STAT(256B_511B);
	p->frames_512_1023  = GET_STAT(512B_1023B);
	p->frames_1024_1518 = GET_STAT(1024B_1518B);
	p->frames_1519_max  = GET_STAT(1519B_MAX);
	p->drop             = GET_STAT(DROP_FRAMES);

	p->ovflow0 = (bgmap & 1) ? GET_STAT_COM(RX_BG_0_LB_DROP_FRAME) : 0;
	p->ovflow1 = (bgmap & 2) ? GET_STAT_COM(RX_BG_1_LB_DROP_FRAME) : 0;
	p->ovflow2 = (bgmap & 4) ? GET_STAT_COM(RX_BG_2_LB_DROP_FRAME) : 0;
	p->ovflow3 = (bgmap & 8) ? GET_STAT_COM(RX_BG_3_LB_DROP_FRAME) : 0;
	p->trunc0 = (bgmap & 1) ? GET_STAT_COM(RX_BG_0_LB_TRUNC_FRAME) : 0;
	p->trunc1 = (bgmap & 2) ? GET_STAT_COM(RX_BG_1_LB_TRUNC_FRAME) : 0;
	p->trunc2 = (bgmap & 4) ? GET_STAT_COM(RX_BG_2_LB_TRUNC_FRAME) : 0;
	p->trunc3 = (bgmap & 8) ? GET_STAT_COM(RX_BG_3_LB_TRUNC_FRAME) : 0;

#undef GET_STAT
#undef GET_STAT_COM
}