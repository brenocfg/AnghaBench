#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_20__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
typedef  size_t word ;
typedef  int /*<<< orphan*/  result ;
typedef  int dword ;
typedef  size_t byte ;
struct TYPE_38__ {size_t length; int /*<<< orphan*/ * info; } ;
struct TYPE_37__ {int appl_flags; } ;
struct TYPE_29__ {int Global_Options; } ;
struct TYPE_36__ {int manufacturer_features; size_t li_channels; size_t li_base; int /*<<< orphan*/  li_pri; TYPE_1__ profile; } ;
struct TYPE_33__ {int /*<<< orphan*/  Id; } ;
struct TYPE_32__ {size_t* info; } ;
struct TYPE_35__ {size_t li_plci_b_write_pos; int* li_plci_b_queue; size_t li_plci_b_read_pos; int li_cmd; int /*<<< orphan*/  command; int /*<<< orphan*/  li_bchannel_id; int /*<<< orphan*/  li_channel_bits; TYPE_5__* adapter; int /*<<< orphan*/  nl_remove_id; TYPE_4__ NL; int /*<<< orphan*/  State; TYPE_3__ saved_msg; } ;
struct TYPE_34__ {size_t li_base; } ;
struct TYPE_31__ {int manufacturer_features; size_t li_base; int /*<<< orphan*/  li_pri; } ;
struct TYPE_30__ {int /*<<< orphan*/  channel; TYPE_6__* plci; TYPE_2__* adapter; } ;
typedef  TYPE_6__ PLCI ;
typedef  TYPE_7__ DIVA_CAPI_ADAPTER ;
typedef  TYPE_8__ APPL ;
typedef  TYPE_9__ API_PARSE ;

/* Variables and functions */
 int APPL_FLAG_OLD_LI_SPEC ; 
 int CONFIRM ; 
 scalar_t__ FILE_ ; 
 int GET_DWORD (int /*<<< orphan*/ *) ; 
 int GET_WORD (int /*<<< orphan*/ *) ; 
 int GL_LINE_INTERCONNECT_SUPPORTED ; 
 size_t GOOD ; 
 int LI2_ASYMMETRIC_SUPPORTED ; 
 int LI2_B_LOOPING_SUPPORTED ; 
 int LI2_CROSS_CONTROLLER_SUPPORTED ; 
 int LI2_FLAG_INTERCONNECT_A_B ; 
 int LI2_FLAG_INTERCONNECT_B_A ; 
 int LI2_FLAG_PCCONNECT_A_B ; 
 int LI2_FLAG_PCCONNECT_B_A ; 
 int LI2_MIXING_SUPPORTED ; 
 int LI2_MONITORING_SUPPORTED ; 
 int LI2_PC_LOOPING_SUPPORTED ; 
 int LI2_REMOTE_MIXING_SUPPORTED ; 
 int LI2_REMOTE_MONITORING_SUPPORTED ; 
 int LI2_X_LOOPING_SUPPORTED ; 
 int LI_ANNOUNCEMENTS_SUPPORTED ; 
 int LI_CONFERENCING_SUPPORTED ; 
 int LI_CROSS_CONTROLLER_SUPPORTED ; 
#define  LI_GET_SUPPORTED_SERVICES 131 
 int LI_MIXING_SUPPORTED ; 
 int LI_MONITORING_SUPPORTED ; 
 int LI_PLCI_B_DISC_FLAG ; 
 int LI_PLCI_B_LAST_FLAG ; 
 size_t LI_PLCI_B_QUEUE_ENTRIES ; 
 int LI_PLCI_B_SKIP_FLAG ; 
#define  LI_REQ_CONNECT 130 
#define  LI_REQ_DISCONNECT 129 
#define  LI_REQ_SILENT_UPDATE 128 
 int MANUFACTURER_FEATURE_MIXER_CH_CH ; 
 int MANUFACTURER_FEATURE_MIXER_CH_PC ; 
 int MANUFACTURER_FEATURE_MIXER_PC_CH ; 
 int MANUFACTURER_FEATURE_MIXER_PC_PC ; 
 int MANUFACTURER_FEATURE_XCONNECT ; 
 size_t MIXER_BCHANNELS_BRI ; 
 int /*<<< orphan*/  PUT_DWORD (size_t*,int) ; 
 int /*<<< orphan*/  PUT_WORD (size_t*,size_t) ; 
 int /*<<< orphan*/  SELECTOR_LINE_INTERCONNECT ; 
 int UnMapId (int) ; 
 size_t _FACILITY_NOT_SUPPORTED ; 
 int _FACILITY_R ; 
 size_t _WRONG_MESSAGE_FORMAT ; 
 size_t _WRONG_STATE ; 
 scalar_t__ api_parse (int /*<<< orphan*/ *,size_t,char*,TYPE_9__*) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int,char*,int,...) ; 
 TYPE_6__* li2_check_plci_b (int,TYPE_6__*,int,size_t,size_t*) ; 
 int /*<<< orphan*/  li2_update_connect (int,TYPE_7__*,TYPE_6__*,int,int,int) ; 
 size_t li_check_main_plci (int,TYPE_6__*) ; 
 TYPE_6__* li_check_plci_b (int,TYPE_6__*,int,size_t,size_t*) ; 
 TYPE_20__* li_config_table ; 
 size_t li_total_channels ; 
 int /*<<< orphan*/  li_update_connect (int,TYPE_7__*,TYPE_6__*,int,int,int) ; 
 int /*<<< orphan*/  mixer_calculate_coefs (TYPE_7__*) ; 
 int /*<<< orphan*/  mixer_command ; 
 int /*<<< orphan*/  mixer_notify_update (TYPE_6__*,int) ; 
 int /*<<< orphan*/  sendf (TYPE_8__*,int,int,size_t,char*,size_t,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  start_internal_command (int,TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static byte mixer_request(dword Id, word Number, DIVA_CAPI_ADAPTER *a, PLCI *plci, APPL   *appl, API_PARSE *msg)
{
	word Info;
	word i;
	dword d, li_flags, plci_b_id;
	PLCI *plci_b;
	API_PARSE li_parms[3];
	API_PARSE li_req_parms[3];
	API_PARSE li_participant_struct[2];
	API_PARSE li_participant_parms[3];
	word participant_parms_pos;
	byte result_buffer[32];
	byte *result;
	word result_pos;
	word plci_b_write_pos;

	dbug(1, dprintf("[%06lx] %s,%d: mixer_request",
			UnMapId(Id), (char *)(FILE_), __LINE__));

	Info = GOOD;
	result = result_buffer;
	result_buffer[0] = 0;
	if (!(a->profile.Global_Options & GL_LINE_INTERCONNECT_SUPPORTED))
	{
		dbug(1, dprintf("[%06lx] %s,%d: Facility not supported",
				UnMapId(Id), (char *)(FILE_), __LINE__));
		Info = _FACILITY_NOT_SUPPORTED;
	}
	else if (api_parse(&msg[1].info[1], msg[1].length, "ws", li_parms))
	{
		dbug(1, dprintf("[%06lx] %s,%d: Wrong message format",
				UnMapId(Id), (char *)(FILE_), __LINE__));
		Info = _WRONG_MESSAGE_FORMAT;
	}
	else
	{
		result_buffer[0] = 3;
		PUT_WORD(&result_buffer[1], GET_WORD(li_parms[0].info));
		result_buffer[3] = 0;
		switch (GET_WORD(li_parms[0].info))
		{
		case LI_GET_SUPPORTED_SERVICES:
			if (appl->appl_flags & APPL_FLAG_OLD_LI_SPEC)
			{
				result_buffer[0] = 17;
				result_buffer[3] = 14;
				PUT_WORD(&result_buffer[4], GOOD);
				d = 0;
				if (a->manufacturer_features & MANUFACTURER_FEATURE_MIXER_CH_CH)
					d |= LI_CONFERENCING_SUPPORTED;
				if (a->manufacturer_features & MANUFACTURER_FEATURE_MIXER_CH_PC)
					d |= LI_MONITORING_SUPPORTED;
				if (a->manufacturer_features & MANUFACTURER_FEATURE_MIXER_PC_CH)
					d |= LI_ANNOUNCEMENTS_SUPPORTED | LI_MIXING_SUPPORTED;
				if (a->manufacturer_features & MANUFACTURER_FEATURE_XCONNECT)
					d |= LI_CROSS_CONTROLLER_SUPPORTED;
				PUT_DWORD(&result_buffer[6], d);
				if (a->manufacturer_features & MANUFACTURER_FEATURE_XCONNECT)
				{
					d = 0;
					for (i = 0; i < li_total_channels; i++)
					{
						if ((li_config_table[i].adapter->manufacturer_features & MANUFACTURER_FEATURE_XCONNECT)
						    && (li_config_table[i].adapter->li_pri
							|| (i < li_config_table[i].adapter->li_base + MIXER_BCHANNELS_BRI)))
						{
							d++;
						}
					}
				}
				else
				{
					d = a->li_pri ? a->li_channels : MIXER_BCHANNELS_BRI;
				}
				PUT_DWORD(&result_buffer[10], d / 2);
				PUT_DWORD(&result_buffer[14], d);
			}
			else
			{
				result_buffer[0] = 25;
				result_buffer[3] = 22;
				PUT_WORD(&result_buffer[4], GOOD);
				d = LI2_ASYMMETRIC_SUPPORTED | LI2_B_LOOPING_SUPPORTED | LI2_X_LOOPING_SUPPORTED;
				if (a->manufacturer_features & MANUFACTURER_FEATURE_MIXER_CH_PC)
					d |= LI2_MONITORING_SUPPORTED | LI2_REMOTE_MONITORING_SUPPORTED;
				if (a->manufacturer_features & MANUFACTURER_FEATURE_MIXER_PC_CH)
					d |= LI2_MIXING_SUPPORTED | LI2_REMOTE_MIXING_SUPPORTED;
				if (a->manufacturer_features & MANUFACTURER_FEATURE_MIXER_PC_PC)
					d |= LI2_PC_LOOPING_SUPPORTED;
				if (a->manufacturer_features & MANUFACTURER_FEATURE_XCONNECT)
					d |= LI2_CROSS_CONTROLLER_SUPPORTED;
				PUT_DWORD(&result_buffer[6], d);
				d = a->li_pri ? a->li_channels : MIXER_BCHANNELS_BRI;
				PUT_DWORD(&result_buffer[10], d / 2);
				PUT_DWORD(&result_buffer[14], d - 1);
				if (a->manufacturer_features & MANUFACTURER_FEATURE_XCONNECT)
				{
					d = 0;
					for (i = 0; i < li_total_channels; i++)
					{
						if ((li_config_table[i].adapter->manufacturer_features & MANUFACTURER_FEATURE_XCONNECT)
						    && (li_config_table[i].adapter->li_pri
							|| (i < li_config_table[i].adapter->li_base + MIXER_BCHANNELS_BRI)))
						{
							d++;
						}
					}
				}
				PUT_DWORD(&result_buffer[18], d / 2);
				PUT_DWORD(&result_buffer[22], d - 1);
			}
			break;

		case LI_REQ_CONNECT:
			if (li_parms[1].length == 8)
			{
				appl->appl_flags |= APPL_FLAG_OLD_LI_SPEC;
				if (api_parse(&li_parms[1].info[1], li_parms[1].length, "dd", li_req_parms))
				{
					dbug(1, dprintf("[%06lx] %s,%d: Wrong message format",
							UnMapId(Id), (char *)(FILE_), __LINE__));
					Info = _WRONG_MESSAGE_FORMAT;
					break;
				}
				plci_b_id = GET_DWORD(li_req_parms[0].info) & 0xffff;
				li_flags = GET_DWORD(li_req_parms[1].info);
				Info = li_check_main_plci(Id, plci);
				result_buffer[0] = 9;
				result_buffer[3] = 6;
				PUT_DWORD(&result_buffer[4], plci_b_id);
				PUT_WORD(&result_buffer[8], GOOD);
				if (Info != GOOD)
					break;
				result = plci->saved_msg.info;
				for (i = 0; i <= result_buffer[0]; i++)
					result[i] = result_buffer[i];
				plci_b_write_pos = plci->li_plci_b_write_pos;
				plci_b = li_check_plci_b(Id, plci, plci_b_id, plci_b_write_pos, &result[8]);
				if (plci_b == NULL)
					break;
				li_update_connect(Id, a, plci, plci_b_id, true, li_flags);
				plci->li_plci_b_queue[plci_b_write_pos] = plci_b_id | LI_PLCI_B_LAST_FLAG;
				plci_b_write_pos = (plci_b_write_pos == LI_PLCI_B_QUEUE_ENTRIES - 1) ? 0 : plci_b_write_pos + 1;
				plci->li_plci_b_write_pos = plci_b_write_pos;
			}
			else
			{
				appl->appl_flags &= ~APPL_FLAG_OLD_LI_SPEC;
				if (api_parse(&li_parms[1].info[1], li_parms[1].length, "ds", li_req_parms))
				{
					dbug(1, dprintf("[%06lx] %s,%d: Wrong message format",
							UnMapId(Id), (char *)(FILE_), __LINE__));
					Info = _WRONG_MESSAGE_FORMAT;
					break;
				}
				li_flags = GET_DWORD(li_req_parms[0].info) & ~(LI2_FLAG_INTERCONNECT_A_B | LI2_FLAG_INTERCONNECT_B_A);
				Info = li_check_main_plci(Id, plci);
				result_buffer[0] = 7;
				result_buffer[3] = 4;
				PUT_WORD(&result_buffer[4], Info);
				result_buffer[6] = 0;
				if (Info != GOOD)
					break;
				result = plci->saved_msg.info;
				for (i = 0; i <= result_buffer[0]; i++)
					result[i] = result_buffer[i];
				plci_b_write_pos = plci->li_plci_b_write_pos;
				participant_parms_pos = 0;
				result_pos = 7;
				li2_update_connect(Id, a, plci, UnMapId(Id), true, li_flags);
				while (participant_parms_pos < li_req_parms[1].length)
				{
					result[result_pos] = 6;
					result_pos += 7;
					PUT_DWORD(&result[result_pos - 6], 0);
					PUT_WORD(&result[result_pos - 2], GOOD);
					if (api_parse(&li_req_parms[1].info[1 + participant_parms_pos],
						      (word)(li_parms[1].length - participant_parms_pos), "s", li_participant_struct))
					{
						dbug(1, dprintf("[%06lx] %s,%d: Wrong message format",
								UnMapId(Id), (char *)(FILE_), __LINE__));
						PUT_WORD(&result[result_pos - 2], _WRONG_MESSAGE_FORMAT);
						break;
					}
					if (api_parse(&li_participant_struct[0].info[1],
						      li_participant_struct[0].length, "dd", li_participant_parms))
					{
						dbug(1, dprintf("[%06lx] %s,%d: Wrong message format",
								UnMapId(Id), (char *)(FILE_), __LINE__));
						PUT_WORD(&result[result_pos - 2], _WRONG_MESSAGE_FORMAT);
						break;
					}
					plci_b_id = GET_DWORD(li_participant_parms[0].info) & 0xffff;
					li_flags = GET_DWORD(li_participant_parms[1].info);
					PUT_DWORD(&result[result_pos - 6], plci_b_id);
					if (sizeof(result) - result_pos < 7)
					{
						dbug(1, dprintf("[%06lx] %s,%d: LI result overrun",
								UnMapId(Id), (char *)(FILE_), __LINE__));
						PUT_WORD(&result[result_pos - 2], _WRONG_STATE);
						break;
					}
					plci_b = li2_check_plci_b(Id, plci, plci_b_id, plci_b_write_pos, &result[result_pos - 2]);
					if (plci_b != NULL)
					{
						li2_update_connect(Id, a, plci, plci_b_id, true, li_flags);
						plci->li_plci_b_queue[plci_b_write_pos] = plci_b_id |
							((li_flags & (LI2_FLAG_INTERCONNECT_A_B | LI2_FLAG_INTERCONNECT_B_A |
								      LI2_FLAG_PCCONNECT_A_B | LI2_FLAG_PCCONNECT_B_A)) ? 0 : LI_PLCI_B_DISC_FLAG);
						plci_b_write_pos = (plci_b_write_pos == LI_PLCI_B_QUEUE_ENTRIES - 1) ? 0 : plci_b_write_pos + 1;
					}
					participant_parms_pos = (word)((&li_participant_struct[0].info[1 + li_participant_struct[0].length]) -
								       (&li_req_parms[1].info[1]));
				}
				result[0] = (byte)(result_pos - 1);
				result[3] = (byte)(result_pos - 4);
				result[6] = (byte)(result_pos - 7);
				i = (plci_b_write_pos == 0) ? LI_PLCI_B_QUEUE_ENTRIES - 1 : plci_b_write_pos - 1;
				if ((plci_b_write_pos == plci->li_plci_b_read_pos)
				    || (plci->li_plci_b_queue[i] & LI_PLCI_B_LAST_FLAG))
				{
					plci->li_plci_b_queue[plci_b_write_pos] = LI_PLCI_B_SKIP_FLAG | LI_PLCI_B_LAST_FLAG;
					plci_b_write_pos = (plci_b_write_pos == LI_PLCI_B_QUEUE_ENTRIES - 1) ? 0 : plci_b_write_pos + 1;
				}
				else
					plci->li_plci_b_queue[i] |= LI_PLCI_B_LAST_FLAG;
				plci->li_plci_b_write_pos = plci_b_write_pos;
			}
			mixer_calculate_coefs(a);
			plci->li_channel_bits = li_config_table[a->li_base + (plci->li_bchannel_id - 1)].channel;
			mixer_notify_update(plci, true);
			sendf(appl, _FACILITY_R | CONFIRM, Id & 0xffffL, Number,
			      "wwS", Info, SELECTOR_LINE_INTERCONNECT, result);
			plci->command = 0;
			plci->li_cmd = GET_WORD(li_parms[0].info);
			start_internal_command(Id, plci, mixer_command);
			return (false);

		case LI_REQ_DISCONNECT:
			if (li_parms[1].length == 4)
			{
				appl->appl_flags |= APPL_FLAG_OLD_LI_SPEC;
				if (api_parse(&li_parms[1].info[1], li_parms[1].length, "d", li_req_parms))
				{
					dbug(1, dprintf("[%06lx] %s,%d: Wrong message format",
							UnMapId(Id), (char *)(FILE_), __LINE__));
					Info = _WRONG_MESSAGE_FORMAT;
					break;
				}
				plci_b_id = GET_DWORD(li_req_parms[0].info) & 0xffff;
				Info = li_check_main_plci(Id, plci);
				result_buffer[0] = 9;
				result_buffer[3] = 6;
				PUT_DWORD(&result_buffer[4], GET_DWORD(li_req_parms[0].info));
				PUT_WORD(&result_buffer[8], GOOD);
				if (Info != GOOD)
					break;
				result = plci->saved_msg.info;
				for (i = 0; i <= result_buffer[0]; i++)
					result[i] = result_buffer[i];
				plci_b_write_pos = plci->li_plci_b_write_pos;
				plci_b = li_check_plci_b(Id, plci, plci_b_id, plci_b_write_pos, &result[8]);
				if (plci_b == NULL)
					break;
				li_update_connect(Id, a, plci, plci_b_id, false, 0);
				plci->li_plci_b_queue[plci_b_write_pos] = plci_b_id | LI_PLCI_B_DISC_FLAG | LI_PLCI_B_LAST_FLAG;
				plci_b_write_pos = (plci_b_write_pos == LI_PLCI_B_QUEUE_ENTRIES - 1) ? 0 : plci_b_write_pos + 1;
				plci->li_plci_b_write_pos = plci_b_write_pos;
			}
			else
			{
				appl->appl_flags &= ~APPL_FLAG_OLD_LI_SPEC;
				if (api_parse(&li_parms[1].info[1], li_parms[1].length, "s", li_req_parms))
				{
					dbug(1, dprintf("[%06lx] %s,%d: Wrong message format",
							UnMapId(Id), (char *)(FILE_), __LINE__));
					Info = _WRONG_MESSAGE_FORMAT;
					break;
				}
				Info = li_check_main_plci(Id, plci);
				result_buffer[0] = 7;
				result_buffer[3] = 4;
				PUT_WORD(&result_buffer[4], Info);
				result_buffer[6] = 0;
				if (Info != GOOD)
					break;
				result = plci->saved_msg.info;
				for (i = 0; i <= result_buffer[0]; i++)
					result[i] = result_buffer[i];
				plci_b_write_pos = plci->li_plci_b_write_pos;
				participant_parms_pos = 0;
				result_pos = 7;
				while (participant_parms_pos < li_req_parms[0].length)
				{
					result[result_pos] = 6;
					result_pos += 7;
					PUT_DWORD(&result[result_pos - 6], 0);
					PUT_WORD(&result[result_pos - 2], GOOD);
					if (api_parse(&li_req_parms[0].info[1 + participant_parms_pos],
						      (word)(li_parms[1].length - participant_parms_pos), "s", li_participant_struct))
					{
						dbug(1, dprintf("[%06lx] %s,%d: Wrong message format",
								UnMapId(Id), (char *)(FILE_), __LINE__));
						PUT_WORD(&result[result_pos - 2], _WRONG_MESSAGE_FORMAT);
						break;
					}
					if (api_parse(&li_participant_struct[0].info[1],
						      li_participant_struct[0].length, "d", li_participant_parms))
					{
						dbug(1, dprintf("[%06lx] %s,%d: Wrong message format",
								UnMapId(Id), (char *)(FILE_), __LINE__));
						PUT_WORD(&result[result_pos - 2], _WRONG_MESSAGE_FORMAT);
						break;
					}
					plci_b_id = GET_DWORD(li_participant_parms[0].info) & 0xffff;
					PUT_DWORD(&result[result_pos - 6], plci_b_id);
					if (sizeof(result) - result_pos < 7)
					{
						dbug(1, dprintf("[%06lx] %s,%d: LI result overrun",
								UnMapId(Id), (char *)(FILE_), __LINE__));
						PUT_WORD(&result[result_pos - 2], _WRONG_STATE);
						break;
					}
					plci_b = li2_check_plci_b(Id, plci, plci_b_id, plci_b_write_pos, &result[result_pos - 2]);
					if (plci_b != NULL)
					{
						li2_update_connect(Id, a, plci, plci_b_id, false, 0);
						plci->li_plci_b_queue[plci_b_write_pos] = plci_b_id | LI_PLCI_B_DISC_FLAG;
						plci_b_write_pos = (plci_b_write_pos == LI_PLCI_B_QUEUE_ENTRIES - 1) ? 0 : plci_b_write_pos + 1;
					}
					participant_parms_pos = (word)((&li_participant_struct[0].info[1 + li_participant_struct[0].length]) -
								       (&li_req_parms[0].info[1]));
				}
				result[0] = (byte)(result_pos - 1);
				result[3] = (byte)(result_pos - 4);
				result[6] = (byte)(result_pos - 7);
				i = (plci_b_write_pos == 0) ? LI_PLCI_B_QUEUE_ENTRIES - 1 : plci_b_write_pos - 1;
				if ((plci_b_write_pos == plci->li_plci_b_read_pos)
				    || (plci->li_plci_b_queue[i] & LI_PLCI_B_LAST_FLAG))
				{
					plci->li_plci_b_queue[plci_b_write_pos] = LI_PLCI_B_SKIP_FLAG | LI_PLCI_B_LAST_FLAG;
					plci_b_write_pos = (plci_b_write_pos == LI_PLCI_B_QUEUE_ENTRIES - 1) ? 0 : plci_b_write_pos + 1;
				}
				else
					plci->li_plci_b_queue[i] |= LI_PLCI_B_LAST_FLAG;
				plci->li_plci_b_write_pos = plci_b_write_pos;
			}
			mixer_calculate_coefs(a);
			plci->li_channel_bits = li_config_table[a->li_base + (plci->li_bchannel_id - 1)].channel;
			mixer_notify_update(plci, true);
			sendf(appl, _FACILITY_R | CONFIRM, Id & 0xffffL, Number,
			      "wwS", Info, SELECTOR_LINE_INTERCONNECT, result);
			plci->command = 0;
			plci->li_cmd = GET_WORD(li_parms[0].info);
			start_internal_command(Id, plci, mixer_command);
			return (false);

		case LI_REQ_SILENT_UPDATE:
			if (!plci || !plci->State
			    || !plci->NL.Id || plci->nl_remove_id
			    || (plci->li_bchannel_id == 0)
			    || (li_config_table[plci->adapter->li_base + (plci->li_bchannel_id - 1)].plci != plci))
			{
				dbug(1, dprintf("[%06lx] %s,%d: Wrong state",
						UnMapId(Id), (char *)(FILE_), __LINE__));
				return (false);
			}
			plci_b_write_pos = plci->li_plci_b_write_pos;
			if (((plci->li_plci_b_read_pos > plci_b_write_pos) ? plci->li_plci_b_read_pos :
			     LI_PLCI_B_QUEUE_ENTRIES + plci->li_plci_b_read_pos) - plci_b_write_pos - 1 < 2)
			{
				dbug(1, dprintf("[%06lx] %s,%d: LI request overrun",
						UnMapId(Id), (char *)(FILE_), __LINE__));
				return (false);
			}
			i = (plci_b_write_pos == 0) ? LI_PLCI_B_QUEUE_ENTRIES - 1 : plci_b_write_pos - 1;
			if ((plci_b_write_pos == plci->li_plci_b_read_pos)
			    || (plci->li_plci_b_queue[i] & LI_PLCI_B_LAST_FLAG))
			{
				plci->li_plci_b_queue[plci_b_write_pos] = LI_PLCI_B_SKIP_FLAG | LI_PLCI_B_LAST_FLAG;
				plci_b_write_pos = (plci_b_write_pos == LI_PLCI_B_QUEUE_ENTRIES - 1) ? 0 : plci_b_write_pos + 1;
			}
			else
				plci->li_plci_b_queue[i] |= LI_PLCI_B_LAST_FLAG;
			plci->li_plci_b_write_pos = plci_b_write_pos;
			plci->li_channel_bits = li_config_table[a->li_base + (plci->li_bchannel_id - 1)].channel;
			plci->command = 0;
			plci->li_cmd = GET_WORD(li_parms[0].info);
			start_internal_command(Id, plci, mixer_command);
			return (false);

		default:
			dbug(1, dprintf("[%06lx] %s,%d: LI unknown request %04x",
					UnMapId(Id), (char *)(FILE_), __LINE__, GET_WORD(li_parms[0].info)));
			Info = _FACILITY_NOT_SUPPORTED;
		}
	}
	sendf(appl, _FACILITY_R | CONFIRM, Id & 0xffffL, Number,
	      "wwS", Info, SELECTOR_LINE_INTERCONNECT, result);
	return (false);
}