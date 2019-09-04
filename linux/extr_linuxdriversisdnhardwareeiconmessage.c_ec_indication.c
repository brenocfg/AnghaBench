#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  word ;
typedef  int dword ;
typedef  int byte ;
struct TYPE_5__ {int appl_flags; } ;
struct TYPE_4__ {int ec_idi_options; TYPE_2__* appl; } ;
typedef  TYPE_1__ PLCI ;

/* Variables and functions */
 int APPL_FLAG_PRIV_EC_SPEC ; 
 int /*<<< orphan*/  EC_BYPASS_DUE_TO_CONTINUOUS_2100HZ ; 
 int /*<<< orphan*/  EC_BYPASS_DUE_TO_REVERSED_2100HZ ; 
 int /*<<< orphan*/  EC_BYPASS_INDICATION ; 
 int /*<<< orphan*/  EC_BYPASS_RELEASED ; 
 scalar_t__ FILE_ ; 
#define  LEC_DISABLE_RELEASED 130 
#define  LEC_DISABLE_TYPE_CONTIGNUOUS_2100HZ 129 
#define  LEC_DISABLE_TYPE_REVERSED_2100HZ 128 
 int LEC_MANUAL_DISABLE ; 
 int /*<<< orphan*/  PRIV_SELECTOR_ECHO_CANCELLER ; 
 int /*<<< orphan*/  PUT_WORD (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SELECTOR_ECHO_CANCELLER ; 
 int /*<<< orphan*/  UnMapId (int) ; 
 int /*<<< orphan*/  _FACILITY_I ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sendf (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void ec_indication(dword Id, PLCI *plci, byte *msg, word length)
{
	byte result[8];

	dbug(1, dprintf("[%06lx] %s,%d: ec_indication",
			UnMapId(Id), (char *)(FILE_), __LINE__));

	if (!(plci->ec_idi_options & LEC_MANUAL_DISABLE))
	{
		if (plci->appl->appl_flags & APPL_FLAG_PRIV_EC_SPEC)
		{
			result[0] = 2;
			PUT_WORD(&result[1], 0);
			switch (msg[1])
			{
			case LEC_DISABLE_TYPE_CONTIGNUOUS_2100HZ:
				PUT_WORD(&result[1], EC_BYPASS_DUE_TO_CONTINUOUS_2100HZ);
				break;
			case LEC_DISABLE_TYPE_REVERSED_2100HZ:
				PUT_WORD(&result[1], EC_BYPASS_DUE_TO_REVERSED_2100HZ);
				break;
			case LEC_DISABLE_RELEASED:
				PUT_WORD(&result[1], EC_BYPASS_RELEASED);
				break;
			}
		}
		else
		{
			result[0] = 5;
			PUT_WORD(&result[1], EC_BYPASS_INDICATION);
			result[3] = 2;
			PUT_WORD(&result[4], 0);
			switch (msg[1])
			{
			case LEC_DISABLE_TYPE_CONTIGNUOUS_2100HZ:
				PUT_WORD(&result[4], EC_BYPASS_DUE_TO_CONTINUOUS_2100HZ);
				break;
			case LEC_DISABLE_TYPE_REVERSED_2100HZ:
				PUT_WORD(&result[4], EC_BYPASS_DUE_TO_REVERSED_2100HZ);
				break;
			case LEC_DISABLE_RELEASED:
				PUT_WORD(&result[4], EC_BYPASS_RELEASED);
				break;
			}
		}
		sendf(plci->appl, _FACILITY_I, Id & 0xffffL, 0, "ws", (plci->appl->appl_flags & APPL_FLAG_PRIV_EC_SPEC) ?
		      PRIV_SELECTOR_ECHO_CANCELLER : SELECTOR_ECHO_CANCELLER, result);
	}
}