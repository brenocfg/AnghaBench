#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t word ;
typedef  int dword ;
typedef  scalar_t__ byte ;
struct TYPE_5__ {scalar_t__ code; int listen_mask; scalar_t__ character; } ;
struct TYPE_4__ {int dtmf_rec_active; scalar_t__ tone_last_indication_code; int /*<<< orphan*/  appl; } ;
typedef  TYPE_1__ PLCI ;

/* Variables and functions */
 size_t DTMF_DIGIT_MAP_ENTRIES ; 
 scalar_t__ DTMF_SIGNAL_NO_TONE ; 
 scalar_t__ DTMF_SIGNAL_UNIDENTIFIED_TONE ; 
 int DTMF_TONE_LISTEN_ACTIVE_FLAG ; 
 scalar_t__ FILE_ ; 
 int /*<<< orphan*/  SELECTOR_DTMF ; 
 int /*<<< orphan*/  UnMapId (int) ; 
 int /*<<< orphan*/  _FACILITY_I ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_3__* dtmf_digit_map ; 
 int /*<<< orphan*/  sendf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void dtmf_indication(dword Id, PLCI *plci, byte *msg, word length)
{
	word i, j, n;

	dbug(1, dprintf("[%06lx] %s,%d: dtmf_indication",
			UnMapId(Id), (char *)(FILE_), __LINE__));

	n = 0;
	for (i = 1; i < length; i++)
	{
		j = 0;
		while ((j < DTMF_DIGIT_MAP_ENTRIES)
		       && ((msg[i] != dtmf_digit_map[j].code)
			   || ((dtmf_digit_map[j].listen_mask & plci->dtmf_rec_active) == 0)))
		{
			j++;
		}
		if (j < DTMF_DIGIT_MAP_ENTRIES)
		{

			if ((dtmf_digit_map[j].listen_mask & DTMF_TONE_LISTEN_ACTIVE_FLAG)
			    && (plci->tone_last_indication_code == DTMF_SIGNAL_NO_TONE)
			    && (dtmf_digit_map[j].character != DTMF_SIGNAL_UNIDENTIFIED_TONE))
			{
				if (n + 1 == i)
				{
					for (i = length; i > n + 1; i--)
						msg[i] = msg[i - 1];
					length++;
					i++;
				}
				msg[++n] = DTMF_SIGNAL_UNIDENTIFIED_TONE;
			}
			plci->tone_last_indication_code = dtmf_digit_map[j].character;

			msg[++n] = dtmf_digit_map[j].character;
		}
	}
	if (n != 0)
	{
		msg[0] = (byte) n;
		sendf(plci->appl, _FACILITY_I, Id & 0xffffL, 0, "wS", SELECTOR_DTMF, msg);
	}
}