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
typedef  int u32 ;
struct altera_jtag {int ir_pre; int ir_post; int jtag_state; int ir_length; int const irstop_state; int /*<<< orphan*/ * ir_buffer; int /*<<< orphan*/  ir_post_data; int /*<<< orphan*/  ir_pre_data; } ;
struct altera_state {struct altera_jtag js; } ;
typedef  enum altera_jtag_state { ____Placeholder_altera_jtag_state } altera_jtag_state ;

/* Variables and functions */
#define  DRCAPTURE 144 
#define  DREXIT1 143 
#define  DREXIT2 142 
#define  DRPAUSE 141 
#define  DRSELECT 140 
#define  DRSHIFT 139 
#define  DRUPDATE 138 
 int ENOMEM ; 
 int EREMOTEIO ; 
#define  IDLE 137 
#define  ILLEGAL_JTAG_STATE 136 
#define  IRCAPTURE 135 
#define  IREXIT1 134 
#define  IREXIT2 133 
#define  IRPAUSE 132 
#define  IRSELECT 131 
#define  IRSHIFT 130 
#define  IRUPDATE 129 
#define  RESET 128 
 int /*<<< orphan*/  alt_jtag_irscan (struct altera_state*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ alt_malloc (int) ; 
 int /*<<< orphan*/  altera_concatenate_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int) ; 
 int altera_goto_jstate (struct altera_state*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

int altera_irscan(struct altera_state *astate,
				u32 count,
				u8 *tdi_data,
				u32 start_index)
/* Shifts data into instruction register */
{
	struct altera_jtag *js = &astate->js;
	int start_code = 0;
	u32 alloc_chars = 0;
	u32 shift_count = js->ir_pre + count + js->ir_post;
	int status = 0;
	enum altera_jtag_state start_state = ILLEGAL_JTAG_STATE;

	switch (js->jtag_state) {
	case ILLEGAL_JTAG_STATE:
	case RESET:
	case IDLE:
		start_code = 0;
		start_state = IDLE;
		break;

	case DRSELECT:
	case DRCAPTURE:
	case DRSHIFT:
	case DREXIT1:
	case DRPAUSE:
	case DREXIT2:
	case DRUPDATE:
		start_code = 1;
		start_state = DRPAUSE;
		break;

	case IRSELECT:
	case IRCAPTURE:
	case IRSHIFT:
	case IREXIT1:
	case IRPAUSE:
	case IREXIT2:
	case IRUPDATE:
		start_code = 2;
		start_state = IRPAUSE;
		break;

	default:
		status = -EREMOTEIO;
		break;
	}

	if (status == 0)
		if (js->jtag_state != start_state)
			status = altera_goto_jstate(astate, start_state);

	if (status == 0) {
		if (shift_count > js->ir_length) {
			alloc_chars = (shift_count + 7) >> 3;
			kfree(js->ir_buffer);
			js->ir_buffer = (u8 *)alt_malloc(alloc_chars);
			if (js->ir_buffer == NULL)
				status = -ENOMEM;
			else
				js->ir_length = alloc_chars * 8;

		}
	}

	if (status == 0) {
		/*
		 * Copy preamble data, IR data,
		 * and postamble data into a buffer
		 */
		altera_concatenate_data(js->ir_buffer,
					js->ir_pre_data,
					js->ir_pre,
					tdi_data,
					start_index,
					count,
					js->ir_post_data,
					js->ir_post);
		/* Do the IRSCAN */
		alt_jtag_irscan(astate,
				start_code,
				shift_count,
				js->ir_buffer,
				NULL);

		/* alt_jtag_irscan() always ends in IRPAUSE state */
		js->jtag_state = IRPAUSE;
	}

	if (status == 0)
		if (js->irstop_state != IRPAUSE)
			status = altera_goto_jstate(astate, js->irstop_state);


	return status;
}