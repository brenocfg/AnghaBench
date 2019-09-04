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
struct altera_jtag {int dr_pre; int dr_post; int jtag_state; int dr_length; int const drstop_state; int /*<<< orphan*/ * dr_buffer; int /*<<< orphan*/  dr_post_data; int /*<<< orphan*/  dr_pre_data; } ;
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
 int /*<<< orphan*/  alt_jtag_drscan (struct altera_state*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ alt_malloc (int) ; 
 int /*<<< orphan*/  altera_concatenate_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int) ; 
 int altera_goto_jstate (struct altera_state*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

int altera_drscan(struct altera_state *astate,
				u32 count,
				u8 *tdi_data,
				u32 start_index)
/* Shifts data into data register (ignoring output data) */
{
	struct altera_jtag *js = &astate->js;
	int start_code = 0;
	u32 alloc_chars = 0;
	u32 shift_count = js->dr_pre + count + js->dr_post;
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
		if (shift_count > js->dr_length) {
			alloc_chars = (shift_count + 7) >> 3;
			kfree(js->dr_buffer);
			js->dr_buffer = (u8 *)alt_malloc(alloc_chars);
			if (js->dr_buffer == NULL)
				status = -ENOMEM;
			else
				js->dr_length = alloc_chars * 8;

		}
	}

	if (status == 0) {
		/*
		 * Copy preamble data, DR data,
		 * and postamble data into a buffer
		 */
		altera_concatenate_data(js->dr_buffer,
					js->dr_pre_data,
					js->dr_pre,
					tdi_data,
					start_index,
					count,
					js->dr_post_data,
					js->dr_post);
		/* Do the DRSCAN */
		alt_jtag_drscan(astate, start_code, shift_count,
				js->dr_buffer, NULL);
		/* alt_jtag_drscan() always ends in DRPAUSE state */
		js->jtag_state = DRPAUSE;
	}

	if (status == 0)
		if (js->drstop_state != DRPAUSE)
			status = altera_goto_jstate(astate, js->drstop_state);

	return status;
}