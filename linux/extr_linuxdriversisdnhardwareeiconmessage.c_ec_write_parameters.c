#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  int /*<<< orphan*/  dword ;
typedef  int byte ;
struct TYPE_8__ {int Id; int ec_idi_options; int ec_tail_length; TYPE_1__* adapter; } ;
struct TYPE_7__ {int /*<<< orphan*/  Id; } ;
typedef  TYPE_2__ PLCI ;

/* Variables and functions */
 int DSP_CTRL_SET_LEC_PARAMETERS ; 
 scalar_t__ FILE_ ; 
 int /*<<< orphan*/  FTY ; 
 int LEC_RESET_COEFFICIENTS ; 
 int /*<<< orphan*/  PUT_WORD (int*,int) ; 
 int /*<<< orphan*/  TEL_CTRL ; 
 int UnMapController (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_p (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  send_req (TYPE_2__*) ; 
 int /*<<< orphan*/  sig_req (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ec_write_parameters(PLCI *plci)
{
	word w;
	byte parameter_buffer[6];

	dbug(1, dprintf("[%06lx] %s,%d: ec_write_parameters",
			(dword)((plci->Id << 8) | UnMapController(plci->adapter->Id)),
			(char *)(FILE_), __LINE__));

	parameter_buffer[0] = 5;
	parameter_buffer[1] = DSP_CTRL_SET_LEC_PARAMETERS;
	PUT_WORD(&parameter_buffer[2], plci->ec_idi_options);
	plci->ec_idi_options &= ~LEC_RESET_COEFFICIENTS;
	w = (plci->ec_tail_length == 0) ? 128 : plci->ec_tail_length;
	PUT_WORD(&parameter_buffer[4], w);
	add_p(plci, FTY, parameter_buffer);
	sig_req(plci, TEL_CTRL, 0);
	send_req(plci);
}