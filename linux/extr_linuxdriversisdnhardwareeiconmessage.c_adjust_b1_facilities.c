#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  int /*<<< orphan*/  dword ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_12__ {int Id; int B1_facilities; TYPE_1__* adapter; } ;
struct TYPE_11__ {int /*<<< orphan*/  Id; } ;
typedef  TYPE_2__ PLCI ;

/* Variables and functions */
 int B1_FACILITY_DTMFR ; 
 int B1_FACILITY_DTMFX ; 
 int B1_FACILITY_EC ; 
 int B1_FACILITY_MIXER ; 
 int B1_FACILITY_VOICE ; 
 scalar_t__ FILE_ ; 
 int UnMapController (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adv_voice_clear_config (TYPE_2__*) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dtmf_parameter_clear_config (TYPE_2__*) ; 
 int /*<<< orphan*/  dtmf_rec_clear_config (TYPE_2__*) ; 
 int /*<<< orphan*/  dtmf_send_clear_config (TYPE_2__*) ; 
 int /*<<< orphan*/  ec_clear_config (TYPE_2__*) ; 
 int get_b1_facilities (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixer_clear_config (TYPE_2__*) ; 

__attribute__((used)) static void adjust_b1_facilities(PLCI *plci, byte new_b1_resource, word new_b1_facilities)
{
	word removed_facilities;

	dbug(1, dprintf("[%06lx] %s,%d: adjust_b1_facilities %d %04x %04x",
			(dword)((plci->Id << 8) | UnMapController(plci->adapter->Id)),
			(char *)(FILE_), __LINE__, new_b1_resource, new_b1_facilities,
			new_b1_facilities & get_b1_facilities(plci, new_b1_resource)));

	new_b1_facilities &= get_b1_facilities(plci, new_b1_resource);
	removed_facilities = plci->B1_facilities & ~new_b1_facilities;

	if (removed_facilities & B1_FACILITY_EC)
		ec_clear_config(plci);


	if (removed_facilities & B1_FACILITY_DTMFR)
	{
		dtmf_rec_clear_config(plci);
		dtmf_parameter_clear_config(plci);
	}
	if (removed_facilities & B1_FACILITY_DTMFX)
		dtmf_send_clear_config(plci);


	if (removed_facilities & B1_FACILITY_MIXER)
		mixer_clear_config(plci);

	if (removed_facilities & B1_FACILITY_VOICE)
		adv_voice_clear_config(plci);
	plci->B1_facilities = new_b1_facilities;
}