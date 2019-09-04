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
typedef  int u16 ;
struct bcm3510_state {int dummy; } ;
struct bcm3510_hab_cmd_tune {int length; int misc; int TUNCTL_state; TYPE_2__* ctl_dat; scalar_t__ clock_width; } ;
typedef  int /*<<< orphan*/  c ;
struct TYPE_3__ {int clk_off; int cs0; int cs1; void* size; } ;
struct TYPE_4__ {int data; TYPE_1__ ctrl; } ;

/* Variables and functions */
 void* BITS_3 ; 
 void* BITS_8 ; 
 int /*<<< orphan*/  CMD_TUNE ; 
 int /*<<< orphan*/  MSGID_TUNE ; 
 int bcm3510_do_hab_cmd (struct bcm3510_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bcm3510_hab_cmd_tune*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm3510_tuner_cmd(struct bcm3510_state* st,u8 bc, u16 n, u8 a)
{
	struct bcm3510_hab_cmd_tune c;
	memset(&c,0,sizeof(struct bcm3510_hab_cmd_tune));

/* I2C Mode disabled,  set 16 control / Data pairs */
	c.length = 0x10;
	c.clock_width = 0;
/* CS1, CS0, DATA, CLK bits control the tuner RF_AGC_SEL pin is set to
 * logic high (as Configuration) */
	c.misc = 0x10;
/* Set duration of the initial state of TUNCTL = 3.34 micro Sec */
	c.TUNCTL_state = 0x40;

/* PRESCALER DIVIDE RATIO | BC1_2_3_4; (band switch), 1stosc REFERENCE COUNTER REF_S12 and REF_S11 */
	c.ctl_dat[0].ctrl.size = BITS_8;
	c.ctl_dat[0].data      = 0x80 | bc;

/* Control DATA pin, 1stosc REFERENCE COUNTER REF_S10 to REF_S3 */
	c.ctl_dat[1].ctrl.size = BITS_8;
	c.ctl_dat[1].data      = 4;

/* set CONTROL BIT 1 to 1, 1stosc REFERENCE COUNTER REF_S2 to REF_S1 */
	c.ctl_dat[2].ctrl.size = BITS_3;
	c.ctl_dat[2].data      = 0x20;

/* control CS0 pin, pulse byte ? */
	c.ctl_dat[3].ctrl.size = BITS_3;
	c.ctl_dat[3].ctrl.clk_off = 1;
	c.ctl_dat[3].ctrl.cs0  = 1;
	c.ctl_dat[3].data      = 0x40;

/* PGM_S18 to PGM_S11 */
	c.ctl_dat[4].ctrl.size = BITS_8;
	c.ctl_dat[4].data      = n >> 3;

/* PGM_S10 to PGM_S8, SWL_S7 to SWL_S3 */
	c.ctl_dat[5].ctrl.size = BITS_8;
	c.ctl_dat[5].data      = ((n & 0x7) << 5) | (a >> 2);

/* SWL_S2 and SWL_S1, set CONTROL BIT 2 to 0 */
	c.ctl_dat[6].ctrl.size = BITS_3;
	c.ctl_dat[6].data      = (a << 6) & 0xdf;

/* control CS0 pin, pulse byte ? */
	c.ctl_dat[7].ctrl.size = BITS_3;
	c.ctl_dat[7].ctrl.clk_off = 1;
	c.ctl_dat[7].ctrl.cs0  = 1;
	c.ctl_dat[7].data      = 0x40;

/* PRESCALER DIVIDE RATIO, 2ndosc REFERENCE COUNTER REF_S12 and REF_S11 */
	c.ctl_dat[8].ctrl.size = BITS_8;
	c.ctl_dat[8].data      = 0x80;

/* 2ndosc REFERENCE COUNTER REF_S10 to REF_S3 */
	c.ctl_dat[9].ctrl.size = BITS_8;
	c.ctl_dat[9].data      = 0x10;

/* set CONTROL BIT 1 to 1, 2ndosc REFERENCE COUNTER REF_S2 to REF_S1 */
	c.ctl_dat[10].ctrl.size = BITS_3;
	c.ctl_dat[10].data      = 0x20;

/* pulse byte */
	c.ctl_dat[11].ctrl.size = BITS_3;
	c.ctl_dat[11].ctrl.clk_off = 1;
	c.ctl_dat[11].ctrl.cs1  = 1;
	c.ctl_dat[11].data      = 0x40;

/* PGM_S18 to PGM_S11 */
	c.ctl_dat[12].ctrl.size = BITS_8;
	c.ctl_dat[12].data      = 0x2a;

/* PGM_S10 to PGM_S8 and SWL_S7 to SWL_S3 */
	c.ctl_dat[13].ctrl.size = BITS_8;
	c.ctl_dat[13].data      = 0x8e;

/* SWL_S2 and SWL_S1 and set CONTROL BIT 2 to 0 */
	c.ctl_dat[14].ctrl.size = BITS_3;
	c.ctl_dat[14].data      = 0;

/* Pulse Byte */
	c.ctl_dat[15].ctrl.size = BITS_3;
	c.ctl_dat[15].ctrl.clk_off = 1;
	c.ctl_dat[15].ctrl.cs1  = 1;
	c.ctl_dat[15].data      = 0x40;

	return bcm3510_do_hab_cmd(st,CMD_TUNE, MSGID_TUNE,(u8 *) &c,sizeof(c), NULL, 0);
}