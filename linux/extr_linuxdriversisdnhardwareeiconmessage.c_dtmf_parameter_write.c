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
struct TYPE_8__ {int Id; int dtmf_parameter_length; int* dtmf_parameter_buffer; TYPE_1__* adapter; } ;
struct TYPE_7__ {int /*<<< orphan*/  Id; } ;
typedef  TYPE_2__ PLCI ;

/* Variables and functions */
 int DSP_CTRL_SET_DTMF_PARAMETERS ; 
 int /*<<< orphan*/  DTMF_PARAMETER_BUFFER_SIZE ; 
 scalar_t__ FILE_ ; 
 int /*<<< orphan*/  FTY ; 
 int /*<<< orphan*/  TEL_CTRL ; 
 int UnMapController (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_p (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  send_req (TYPE_2__*) ; 
 int /*<<< orphan*/  sig_req (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dtmf_parameter_write(PLCI *plci)
{
	word i;
	byte parameter_buffer[DTMF_PARAMETER_BUFFER_SIZE + 2];

	dbug(1, dprintf("[%06lx] %s,%d: dtmf_parameter_write",
			(dword)((plci->Id << 8) | UnMapController(plci->adapter->Id)),
			(char *)(FILE_), __LINE__));

	parameter_buffer[0] = plci->dtmf_parameter_length + 1;
	parameter_buffer[1] = DSP_CTRL_SET_DTMF_PARAMETERS;
	for (i = 0; i < plci->dtmf_parameter_length; i++)
		parameter_buffer[2 + i] = plci->dtmf_parameter_buffer[i];
	add_p(plci, FTY, parameter_buffer);
	sig_req(plci, TEL_CTRL, 0);
	send_req(plci);
}