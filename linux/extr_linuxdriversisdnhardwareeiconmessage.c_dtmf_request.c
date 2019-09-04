#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;

/* Type definitions */
typedef  int word ;
typedef  int dword ;
typedef  int byte ;
struct TYPE_24__ {int* info; int length; } ;
struct TYPE_23__ {int Id; } ;
struct TYPE_20__ {int Global_Options; } ;
struct TYPE_22__ {long* requested_options_table; int manufacturer_features; TYPE_3__ profile; } ;
struct TYPE_18__ {int /*<<< orphan*/  Id; } ;
struct TYPE_21__ {scalar_t__ dtmf_cmd; long requested_options_conn; long requested_options; int /*<<< orphan*/  saved_msg; int /*<<< orphan*/  dtmf_msg_number_queue; int /*<<< orphan*/  dtmf_send_requests; scalar_t__ dtmf_send_pause_ms; scalar_t__ dtmf_send_pulse_ms; TYPE_2__* adapter; scalar_t__ dtmf_rec_pause_ms; scalar_t__ dtmf_rec_pulse_ms; scalar_t__ command; scalar_t__ nl_remove_id; TYPE_1__ NL; int /*<<< orphan*/  State; } ;
struct TYPE_19__ {long* requested_options_table; } ;
struct TYPE_17__ {scalar_t__ listen_mask; int character; scalar_t__ send_mask; } ;
typedef  TYPE_4__ PLCI ;
typedef  TYPE_5__ DIVA_CAPI_ADAPTER ;
typedef  TYPE_6__ APPL ;
typedef  TYPE_7__ API_PARSE ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int CONFIRM ; 
#define  DTMF_DIGITS_SEND 136 
 int DTMF_DIGIT_MAP_ENTRIES ; 
 scalar_t__ DTMF_GET_SUPPORTED_DETECT_CODES ; 
 scalar_t__ DTMF_GET_SUPPORTED_SEND_CODES ; 
 int /*<<< orphan*/  DTMF_INCORRECT_DIGIT ; 
 int DTMF_LISTEN_ACTIVE_FLAG ; 
#define  DTMF_LISTEN_MF_START 135 
#define  DTMF_LISTEN_MF_STOP 134 
#define  DTMF_LISTEN_START 133 
#define  DTMF_LISTEN_STOP 132 
#define  DTMF_LISTEN_TONE_START 131 
#define  DTMF_LISTEN_TONE_STOP 130 
#define  DTMF_SEND_MF 129 
#define  DTMF_SEND_TONE 128 
 int /*<<< orphan*/  DTMF_SUCCESS ; 
 int /*<<< orphan*/  DTMF_UNKNOWN_REQUEST ; 
 scalar_t__ FILE_ ; 
 scalar_t__ GET_WORD (int*) ; 
 int GL_DTMF_SUPPORTED ; 
 int GOOD ; 
 int MANUFACTURER_FEATURE_HARDDTMF ; 
 int MANUFACTURER_FEATURE_SOFTDTMF_RECEIVE ; 
 long PRIVATE_DTMF_TONE ; 
 int /*<<< orphan*/  PUT_WORD (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SELECTOR_DTMF ; 
 int /*<<< orphan*/  UnMapId (int) ; 
 int _FACILITY_NOT_SUPPORTED ; 
 int _FACILITY_R ; 
 int _WRONG_IDENTIFIER ; 
 int _WRONG_MESSAGE_FORMAT ; 
 int _WRONG_STATE ; 
 scalar_t__ api_parse (int*,int,char*,TYPE_7__*) ; 
 int /*<<< orphan*/  api_save_msg (TYPE_7__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dtmf_command ; 
 TYPE_14__* dtmf_digit_map ; 
 int /*<<< orphan*/  sendf (TYPE_6__*,int,int,int,char*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  start_internal_command (int,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static byte dtmf_request(dword Id, word Number, DIVA_CAPI_ADAPTER *a, PLCI *plci, APPL   *appl, API_PARSE *msg)
{
	word Info;
	word i, j;
	byte mask;
	API_PARSE dtmf_parms[5];
	byte result[40];

	dbug(1, dprintf("[%06lx] %s,%d: dtmf_request",
			UnMapId(Id), (char *)(FILE_), __LINE__));

	Info = GOOD;
	result[0] = 2;
	PUT_WORD(&result[1], DTMF_SUCCESS);
	if (!(a->profile.Global_Options & GL_DTMF_SUPPORTED))
	{
		dbug(1, dprintf("[%06lx] %s,%d: Facility not supported",
				UnMapId(Id), (char *)(FILE_), __LINE__));
		Info = _FACILITY_NOT_SUPPORTED;
	}
	else if (api_parse(&msg[1].info[1], msg[1].length, "w", dtmf_parms))
	{
		dbug(1, dprintf("[%06lx] %s,%d: Wrong message format",
				UnMapId(Id), (char *)(FILE_), __LINE__));
		Info = _WRONG_MESSAGE_FORMAT;
	}

	else if ((GET_WORD(dtmf_parms[0].info) == DTMF_GET_SUPPORTED_DETECT_CODES)
		 || (GET_WORD(dtmf_parms[0].info) == DTMF_GET_SUPPORTED_SEND_CODES))
	{
		if (!((a->requested_options_table[appl->Id - 1])
		      & (1L << PRIVATE_DTMF_TONE)))
		{
			dbug(1, dprintf("[%06lx] %s,%d: DTMF unknown request %04x",
					UnMapId(Id), (char *)(FILE_), __LINE__, GET_WORD(dtmf_parms[0].info)));
			PUT_WORD(&result[1], DTMF_UNKNOWN_REQUEST);
		}
		else
		{
			for (i = 0; i < 32; i++)
				result[4 + i] = 0;
			if (GET_WORD(dtmf_parms[0].info) == DTMF_GET_SUPPORTED_DETECT_CODES)
			{
				for (i = 0; i < DTMF_DIGIT_MAP_ENTRIES; i++)
				{
					if (dtmf_digit_map[i].listen_mask != 0)
						result[4 + (dtmf_digit_map[i].character >> 3)] |= (1 << (dtmf_digit_map[i].character & 0x7));
				}
			}
			else
			{
				for (i = 0; i < DTMF_DIGIT_MAP_ENTRIES; i++)
				{
					if (dtmf_digit_map[i].send_mask != 0)
						result[4 + (dtmf_digit_map[i].character >> 3)] |= (1 << (dtmf_digit_map[i].character & 0x7));
				}
			}
			result[0] = 3 + 32;
			result[3] = 32;
		}
	}

	else if (plci == NULL)
	{
		dbug(1, dprintf("[%06lx] %s,%d: Wrong PLCI",
				UnMapId(Id), (char *)(FILE_), __LINE__));
		Info = _WRONG_IDENTIFIER;
	}
	else
	{
		if (!plci->State
		    || !plci->NL.Id || plci->nl_remove_id)
		{
			dbug(1, dprintf("[%06lx] %s,%d: Wrong state",
					UnMapId(Id), (char *)(FILE_), __LINE__));
			Info = _WRONG_STATE;
		}
		else
		{
			plci->command = 0;
			plci->dtmf_cmd = GET_WORD(dtmf_parms[0].info);
			mask = 0x01;
			switch (plci->dtmf_cmd)
			{

			case DTMF_LISTEN_TONE_START:
			case DTMF_LISTEN_TONE_STOP:
				mask <<= 1; /* fall through */
			case DTMF_LISTEN_MF_START:
			case DTMF_LISTEN_MF_STOP:
				mask <<= 1;
				if (!((plci->requested_options_conn | plci->requested_options | plci->adapter->requested_options_table[appl->Id - 1])
				      & (1L << PRIVATE_DTMF_TONE)))
				{
					dbug(1, dprintf("[%06lx] %s,%d: DTMF unknown request %04x",
							UnMapId(Id), (char *)(FILE_), __LINE__, GET_WORD(dtmf_parms[0].info)));
					PUT_WORD(&result[1], DTMF_UNKNOWN_REQUEST);
					break;
				}
				/* fall through */

			case DTMF_LISTEN_START:
			case DTMF_LISTEN_STOP:
				if (!(a->manufacturer_features & MANUFACTURER_FEATURE_HARDDTMF)
				    && !(a->manufacturer_features & MANUFACTURER_FEATURE_SOFTDTMF_RECEIVE))
				{
					dbug(1, dprintf("[%06lx] %s,%d: Facility not supported",
							UnMapId(Id), (char *)(FILE_), __LINE__));
					Info = _FACILITY_NOT_SUPPORTED;
					break;
				}
				if (mask & DTMF_LISTEN_ACTIVE_FLAG)
				{
					if (api_parse(&msg[1].info[1], msg[1].length, "wwws", dtmf_parms))
					{
						plci->dtmf_rec_pulse_ms = 0;
						plci->dtmf_rec_pause_ms = 0;
					}
					else
					{
						plci->dtmf_rec_pulse_ms = GET_WORD(dtmf_parms[1].info);
						plci->dtmf_rec_pause_ms = GET_WORD(dtmf_parms[2].info);
					}
				}
				start_internal_command(Id, plci, dtmf_command);
				return (false);


			case DTMF_SEND_TONE:
				mask <<= 1; /* fall through */
			case DTMF_SEND_MF:
				mask <<= 1;
				if (!((plci->requested_options_conn | plci->requested_options | plci->adapter->requested_options_table[appl->Id - 1])
				      & (1L << PRIVATE_DTMF_TONE)))
				{
					dbug(1, dprintf("[%06lx] %s,%d: DTMF unknown request %04x",
							UnMapId(Id), (char *)(FILE_), __LINE__, GET_WORD(dtmf_parms[0].info)));
					PUT_WORD(&result[1], DTMF_UNKNOWN_REQUEST);
					break;
				}
				/* fall through */

			case DTMF_DIGITS_SEND:
				if (api_parse(&msg[1].info[1], msg[1].length, "wwws", dtmf_parms))
				{
					dbug(1, dprintf("[%06lx] %s,%d: Wrong message format",
							UnMapId(Id), (char *)(FILE_), __LINE__));
					Info = _WRONG_MESSAGE_FORMAT;
					break;
				}
				if (mask & DTMF_LISTEN_ACTIVE_FLAG)
				{
					plci->dtmf_send_pulse_ms = GET_WORD(dtmf_parms[1].info);
					plci->dtmf_send_pause_ms = GET_WORD(dtmf_parms[2].info);
				}
				i = 0;
				j = 0;
				while ((i < dtmf_parms[3].length) && (j < DTMF_DIGIT_MAP_ENTRIES))
				{
					j = 0;
					while ((j < DTMF_DIGIT_MAP_ENTRIES)
					       && ((dtmf_parms[3].info[i + 1] != dtmf_digit_map[j].character)
						   || ((dtmf_digit_map[j].send_mask & mask) == 0)))
					{
						j++;
					}
					i++;
				}
				if (j == DTMF_DIGIT_MAP_ENTRIES)
				{
					dbug(1, dprintf("[%06lx] %s,%d: Incorrect DTMF digit %02x",
							UnMapId(Id), (char *)(FILE_), __LINE__, dtmf_parms[3].info[i]));
					PUT_WORD(&result[1], DTMF_INCORRECT_DIGIT);
					break;
				}
				if (plci->dtmf_send_requests >= ARRAY_SIZE(plci->dtmf_msg_number_queue))
				{
					dbug(1, dprintf("[%06lx] %s,%d: DTMF request overrun",
							UnMapId(Id), (char *)(FILE_), __LINE__));
					Info = _WRONG_STATE;
					break;
				}
				api_save_msg(dtmf_parms, "wwws", &plci->saved_msg);
				start_internal_command(Id, plci, dtmf_command);
				return (false);

			default:
				dbug(1, dprintf("[%06lx] %s,%d: DTMF unknown request %04x",
						UnMapId(Id), (char *)(FILE_), __LINE__, plci->dtmf_cmd));
				PUT_WORD(&result[1], DTMF_UNKNOWN_REQUEST);
			}
		}
	}
	sendf(appl, _FACILITY_R | CONFIRM, Id & 0xffffL, Number,
	      "wws", Info, SELECTOR_DTMF, result);
	return (false);
}