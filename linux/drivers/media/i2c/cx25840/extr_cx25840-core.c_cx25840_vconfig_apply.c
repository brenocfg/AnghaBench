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
struct i2c_client {int dummy; } ;
struct cx25840_state {int vid_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX25840_VCONFIG_ACTIVE_HORIZONTAL ; 
 int /*<<< orphan*/  CX25840_VCONFIG_ACTIVE_MASK ; 
 int /*<<< orphan*/  CX25840_VCONFIG_ANCDATA_ENABLED ; 
 int /*<<< orphan*/  CX25840_VCONFIG_ANCDATA_MASK ; 
 int CX25840_VCONFIG_CLKGATE_MASK ; 
#define  CX25840_VCONFIG_CLKGATE_NONE 134 
#define  CX25840_VCONFIG_CLKGATE_VALID 133 
#define  CX25840_VCONFIG_CLKGATE_VALIDACTIVE 132 
 int /*<<< orphan*/  CX25840_VCONFIG_DCMODE_BYTES ; 
 int /*<<< orphan*/  CX25840_VCONFIG_DCMODE_MASK ; 
#define  CX25840_VCONFIG_FMT_BT601 131 
#define  CX25840_VCONFIG_FMT_BT656 130 
 int CX25840_VCONFIG_FMT_MASK ; 
#define  CX25840_VCONFIG_FMT_VIP11 129 
#define  CX25840_VCONFIG_FMT_VIP2 128 
 int /*<<< orphan*/  CX25840_VCONFIG_HRESETW_MASK ; 
 int /*<<< orphan*/  CX25840_VCONFIG_HRESETW_PIXCLK ; 
 int /*<<< orphan*/  CX25840_VCONFIG_IDID0S_LINECNT ; 
 int /*<<< orphan*/  CX25840_VCONFIG_IDID0S_MASK ; 
 int /*<<< orphan*/  CX25840_VCONFIG_RES_10BIT ; 
 int /*<<< orphan*/  CX25840_VCONFIG_RES_MASK ; 
 int /*<<< orphan*/  CX25840_VCONFIG_SET_BIT (struct cx25840_state*,int /*<<< orphan*/ ,int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CX25840_VCONFIG_TASKBIT_MASK ; 
 int /*<<< orphan*/  CX25840_VCONFIG_TASKBIT_ONE ; 
 int /*<<< orphan*/  CX25840_VCONFIG_VALID_ANDACTIVE ; 
 int /*<<< orphan*/  CX25840_VCONFIG_VALID_MASK ; 
 int /*<<< orphan*/  CX25840_VCONFIG_VBIRAW_ENABLED ; 
 int /*<<< orphan*/  CX25840_VCONFIG_VBIRAW_MASK ; 
 int /*<<< orphan*/  CX25840_VCONFIG_VIPCLAMP_ENABLED ; 
 int /*<<< orphan*/  CX25840_VCONFIG_VIPCLAMP_MASK ; 
 int cx25840_read (struct i2c_client*,int) ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 struct cx25840_state* to_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cx25840_vconfig_apply(struct i2c_client *client)
{
	struct cx25840_state *state = to_state(i2c_get_clientdata(client));
	u8 voutctrl[3];
	unsigned int i;

	for (i = 0; i < 3; i++)
		voutctrl[i] = cx25840_read(client, 0x404 + i);

	if (state->vid_config & CX25840_VCONFIG_FMT_MASK)
		voutctrl[0] &= ~3;
	switch (state->vid_config & CX25840_VCONFIG_FMT_MASK) {
	case CX25840_VCONFIG_FMT_BT656:
		voutctrl[0] |= 1;
		break;

	case CX25840_VCONFIG_FMT_VIP11:
		voutctrl[0] |= 2;
		break;

	case CX25840_VCONFIG_FMT_VIP2:
		voutctrl[0] |= 3;
		break;

	case CX25840_VCONFIG_FMT_BT601:
		/* zero */
	default:
		break;
	}

	CX25840_VCONFIG_SET_BIT(state, CX25840_VCONFIG_RES_MASK, voutctrl,
				0, 2, CX25840_VCONFIG_RES_10BIT);
	CX25840_VCONFIG_SET_BIT(state, CX25840_VCONFIG_VBIRAW_MASK, voutctrl,
				0, 3, CX25840_VCONFIG_VBIRAW_ENABLED);
	CX25840_VCONFIG_SET_BIT(state, CX25840_VCONFIG_ANCDATA_MASK, voutctrl,
				0, 4, CX25840_VCONFIG_ANCDATA_ENABLED);
	CX25840_VCONFIG_SET_BIT(state, CX25840_VCONFIG_TASKBIT_MASK, voutctrl,
				0, 5, CX25840_VCONFIG_TASKBIT_ONE);
	CX25840_VCONFIG_SET_BIT(state, CX25840_VCONFIG_ACTIVE_MASK, voutctrl,
				1, 2, CX25840_VCONFIG_ACTIVE_HORIZONTAL);
	CX25840_VCONFIG_SET_BIT(state, CX25840_VCONFIG_VALID_MASK, voutctrl,
				1, 3, CX25840_VCONFIG_VALID_ANDACTIVE);
	CX25840_VCONFIG_SET_BIT(state, CX25840_VCONFIG_HRESETW_MASK, voutctrl,
				1, 4, CX25840_VCONFIG_HRESETW_PIXCLK);

	if (state->vid_config & CX25840_VCONFIG_CLKGATE_MASK)
		voutctrl[1] &= ~(3 << 6);
	switch (state->vid_config & CX25840_VCONFIG_CLKGATE_MASK) {
	case CX25840_VCONFIG_CLKGATE_VALID:
		voutctrl[1] |= 2;
		break;

	case CX25840_VCONFIG_CLKGATE_VALIDACTIVE:
		voutctrl[1] |= 3;
		break;

	case CX25840_VCONFIG_CLKGATE_NONE:
		/* zero */
	default:
		break;
	}

	CX25840_VCONFIG_SET_BIT(state, CX25840_VCONFIG_DCMODE_MASK, voutctrl,
				2, 0, CX25840_VCONFIG_DCMODE_BYTES);
	CX25840_VCONFIG_SET_BIT(state, CX25840_VCONFIG_IDID0S_MASK, voutctrl,
				2, 1, CX25840_VCONFIG_IDID0S_LINECNT);
	CX25840_VCONFIG_SET_BIT(state, CX25840_VCONFIG_VIPCLAMP_MASK, voutctrl,
				2, 4, CX25840_VCONFIG_VIPCLAMP_ENABLED);

	for (i = 0; i < 3; i++)
		cx25840_write(client, 0x404 + i, voutctrl[i]);
}