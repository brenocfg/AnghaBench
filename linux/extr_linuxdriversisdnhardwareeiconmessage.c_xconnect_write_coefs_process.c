#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
typedef  size_t word ;
struct TYPE_16__ {int low; int high; } ;
struct xconnect_transfer_address_s {int offset; TYPE_2__ card_address; } ;
typedef  int dword ;
typedef  int /*<<< orphan*/  ch_map ;
typedef  int byte ;
struct TYPE_21__ {int Req; scalar_t__ ReqCh; TYPE_3__* X; } ;
struct TYPE_20__ {size_t mask; size_t to_ch; size_t from_ch; scalar_t__ xconnect_override; int line_flags; scalar_t__ to_pc; scalar_t__ from_pc; } ;
struct TYPE_19__ {int li_base; int manufacturer_features; int adv_voice_coef_length; int* adv_voice_coef_buffer; int /*<<< orphan*/  (* request ) (TYPE_8__*) ;TYPE_4__* AdvSignalPLCI; scalar_t__ li_pri; } ;
struct TYPE_18__ {size_t li_write_channel; int li_bchannel_id; int* internal_req_buffer; scalar_t__ tel; int nl_req; TYPE_8__ NL; TYPE_5__* adapter; TYPE_3__* NData; int /*<<< orphan*/  li_write_command; int /*<<< orphan*/  internal_command; } ;
struct TYPE_17__ {int* P; int PLength; } ;
struct TYPE_15__ {int manufacturer_features; size_t li_base; int /*<<< orphan*/  li_pri; scalar_t__ u_law; } ;
struct TYPE_14__ {int channel; int* coef_table; struct xconnect_transfer_address_s send_pc; struct xconnect_transfer_address_s send_b; TYPE_1__* adapter; TYPE_4__* plci; } ;
typedef  TYPE_4__ PLCI ;
typedef  TYPE_5__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
 scalar_t__ ADV_VOICE ; 
 int ADV_VOICE_NEW_COEF_BASE ; 
 size_t ARRAY_SIZE (TYPE_6__*) ; 
 scalar_t__ FILE_ ; 
 size_t GET_WORD (int*) ; 
 int INTERNAL_REQ_BUFFER_SIZE ; 
 int LI_CHANNEL_ADDRESSES_SET ; 
 int LI_CHANNEL_INVOLVED ; 
 int LI_CHANNEL_RX_DATA ; 
 int LI_CHANNEL_TX_DATA ; 
 size_t LI_COEF_CH_CH ; 
 size_t LI_COEF_CH_PC ; 
 size_t LI_COEF_PC_CH ; 
 size_t LI_COEF_PC_PC ; 
 int MANUFACTURER_FEATURE_DMACONNECT ; 
 int MANUFACTURER_FEATURE_XCONNECT ; 
 size_t MIXER_BCHANNELS_BRI ; 
 int MIXER_CHANNELS_BRI ; 
 size_t MIXER_CHANNELS_PRI ; 
 int MIXER_COEF_LINE_ROW_FLAG ; 
 size_t MIXER_FEATURE_ENABLE_RX_DATA ; 
 size_t MIXER_FEATURE_ENABLE_TX_DATA ; 
 scalar_t__ N_UDATA ; 
 int OK ; 
 int OK_FC ; 
 void* UDATA_REQUEST_SET_MIXER_COEFS_BRI ; 
 void* UDATA_REQUEST_SET_MIXER_COEFS_PRI_SYNC ; 
 int /*<<< orphan*/  UDATA_REQUEST_XCONNECT_TO ; 
 int /*<<< orphan*/  UnMapId (int) ; 
 size_t XCONNECT_CHANNEL_PORT_PC ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,...) ; 
 TYPE_12__* li_config_table ; 
 size_t li_total_channels ; 
 size_t* mixer_swapped_index_bri ; 
 TYPE_6__* mixer_write_prog_bri ; 
 TYPE_6__* mixer_write_prog_pri ; 
 scalar_t__ plci_nl_busy (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*) ; 
 TYPE_6__* xconnect_write_prog ; 

__attribute__((used)) static byte xconnect_write_coefs_process(dword Id, PLCI *plci, byte Rc)
{
	DIVA_CAPI_ADAPTER *a;
	word w, n, i, j, r, s, to_ch;
	dword d;
	byte *p;
	struct xconnect_transfer_address_s   *transfer_address;
	byte ch_map[MIXER_CHANNELS_BRI];

	dbug(1, dprintf("[%06x] %s,%d: xconnect_write_coefs_process %02x %d",
			UnMapId(Id), (char *)(FILE_), __LINE__, Rc, plci->li_write_channel));

	a = plci->adapter;
	if ((plci->li_bchannel_id == 0)
	    || (li_config_table[a->li_base + (plci->li_bchannel_id - 1)].plci != plci))
	{
		dbug(1, dprintf("[%06x] %s,%d: Channel id wiped out",
				UnMapId(Id), (char *)(FILE_), __LINE__));
		return (true);
	}
	i = a->li_base + (plci->li_bchannel_id - 1);
	j = plci->li_write_channel;
	p = plci->internal_req_buffer;
	if (j != 0)
	{
		if ((Rc != OK) && (Rc != OK_FC))
		{
			dbug(1, dprintf("[%06lx] %s,%d: LI write coefs failed %02x",
					UnMapId(Id), (char *)(FILE_), __LINE__, Rc));
			return (false);
		}
	}
	if (li_config_table[i].adapter->manufacturer_features & MANUFACTURER_FEATURE_XCONNECT)
	{
		r = 0;
		s = 0;
		if (j < li_total_channels)
		{
			if (li_config_table[i].channel & LI_CHANNEL_ADDRESSES_SET)
			{
				s = ((li_config_table[i].send_b.card_address.low | li_config_table[i].send_b.card_address.high) ?
				     (LI_COEF_CH_CH | LI_COEF_CH_PC | LI_COEF_PC_CH | LI_COEF_PC_PC) : (LI_COEF_CH_PC | LI_COEF_PC_PC)) &
					((li_config_table[i].send_pc.card_address.low | li_config_table[i].send_pc.card_address.high) ?
					 (LI_COEF_CH_CH | LI_COEF_CH_PC | LI_COEF_PC_CH | LI_COEF_PC_PC) : (LI_COEF_CH_CH | LI_COEF_PC_CH));
			}
			r = ((li_config_table[i].coef_table[j] & 0xf) ^ (li_config_table[i].coef_table[j] >> 4));
			while ((j < li_total_channels)
			       && ((r == 0)
				   || (!(li_config_table[j].channel & LI_CHANNEL_ADDRESSES_SET))
				   || (!li_config_table[j].adapter->li_pri
				       && (j >= li_config_table[j].adapter->li_base + MIXER_BCHANNELS_BRI))
				   || (((li_config_table[j].send_b.card_address.low != li_config_table[i].send_b.card_address.low)
					|| (li_config_table[j].send_b.card_address.high != li_config_table[i].send_b.card_address.high))
				       && (!(a->manufacturer_features & MANUFACTURER_FEATURE_DMACONNECT)
					   || !(li_config_table[j].adapter->manufacturer_features & MANUFACTURER_FEATURE_DMACONNECT)))
				   || ((li_config_table[j].adapter->li_base != a->li_base)
				       && !(r & s &
					    ((li_config_table[j].send_b.card_address.low | li_config_table[j].send_b.card_address.high) ?
					     (LI_COEF_CH_CH | LI_COEF_CH_PC | LI_COEF_PC_CH | LI_COEF_PC_PC) : (LI_COEF_PC_CH | LI_COEF_PC_PC)) &
					    ((li_config_table[j].send_pc.card_address.low | li_config_table[j].send_pc.card_address.high) ?
					     (LI_COEF_CH_CH | LI_COEF_CH_PC | LI_COEF_PC_CH | LI_COEF_PC_PC) : (LI_COEF_CH_CH | LI_COEF_CH_PC))))))
			{
				j++;
				if (j < li_total_channels)
					r = ((li_config_table[i].coef_table[j] & 0xf) ^ (li_config_table[i].coef_table[j] >> 4));
			}
		}
		if (j < li_total_channels)
		{
			plci->internal_command = plci->li_write_command;
			if (plci_nl_busy(plci))
				return (true);
			to_ch = (a->li_pri) ? plci->li_bchannel_id - 1 : 0;
			*(p++) = UDATA_REQUEST_XCONNECT_TO;
			do
			{
				if (li_config_table[j].adapter->li_base != a->li_base)
				{
					r &= s &
						((li_config_table[j].send_b.card_address.low | li_config_table[j].send_b.card_address.high) ?
						 (LI_COEF_CH_CH | LI_COEF_CH_PC | LI_COEF_PC_CH | LI_COEF_PC_PC) : (LI_COEF_PC_CH | LI_COEF_PC_PC)) &
						((li_config_table[j].send_pc.card_address.low | li_config_table[j].send_pc.card_address.high) ?
						 (LI_COEF_CH_CH | LI_COEF_CH_PC | LI_COEF_PC_CH | LI_COEF_PC_PC) : (LI_COEF_CH_CH | LI_COEF_CH_PC));
				}
				n = 0;
				do
				{
					if (r & xconnect_write_prog[n].mask)
					{
						if (xconnect_write_prog[n].from_pc)
							transfer_address = &(li_config_table[j].send_pc);
						else
							transfer_address = &(li_config_table[j].send_b);
						d = transfer_address->card_address.low;
						*(p++) = (byte) d;
						*(p++) = (byte)(d >> 8);
						*(p++) = (byte)(d >> 16);
						*(p++) = (byte)(d >> 24);
						d = transfer_address->card_address.high;
						*(p++) = (byte) d;
						*(p++) = (byte)(d >> 8);
						*(p++) = (byte)(d >> 16);
						*(p++) = (byte)(d >> 24);
						d = transfer_address->offset;
						*(p++) = (byte) d;
						*(p++) = (byte)(d >> 8);
						*(p++) = (byte)(d >> 16);
						*(p++) = (byte)(d >> 24);
						w = xconnect_write_prog[n].to_pc ? to_ch | XCONNECT_CHANNEL_PORT_PC : to_ch;
						*(p++) = (byte) w;
						*(p++) = (byte)(w >> 8);
						w = ((li_config_table[i].coef_table[j] & xconnect_write_prog[n].mask) == 0) ? 0x01 :
							(li_config_table[i].adapter->u_law ?
							 (li_config_table[j].adapter->u_law ? 0x80 : 0x86) :
							 (li_config_table[j].adapter->u_law ? 0x7a : 0x80));
						*(p++) = (byte) w;
						*(p++) = (byte) 0;
						li_config_table[i].coef_table[j] ^= xconnect_write_prog[n].mask << 4;
					}
					n++;
				} while ((n < ARRAY_SIZE(xconnect_write_prog))
					 && ((p - plci->internal_req_buffer) + 16 < INTERNAL_REQ_BUFFER_SIZE));
				if (n == ARRAY_SIZE(xconnect_write_prog))
				{
					do
					{
						j++;
						if (j < li_total_channels)
							r = ((li_config_table[i].coef_table[j] & 0xf) ^ (li_config_table[i].coef_table[j] >> 4));
					} while ((j < li_total_channels)
						 && ((r == 0)
						     || (!(li_config_table[j].channel & LI_CHANNEL_ADDRESSES_SET))
						     || (!li_config_table[j].adapter->li_pri
							 && (j >= li_config_table[j].adapter->li_base + MIXER_BCHANNELS_BRI))
						     || (((li_config_table[j].send_b.card_address.low != li_config_table[i].send_b.card_address.low)
							  || (li_config_table[j].send_b.card_address.high != li_config_table[i].send_b.card_address.high))
							 && (!(a->manufacturer_features & MANUFACTURER_FEATURE_DMACONNECT)
							     || !(li_config_table[j].adapter->manufacturer_features & MANUFACTURER_FEATURE_DMACONNECT)))
						     || ((li_config_table[j].adapter->li_base != a->li_base)
							 && !(r & s &
							      ((li_config_table[j].send_b.card_address.low | li_config_table[j].send_b.card_address.high) ?
							       (LI_COEF_CH_CH | LI_COEF_CH_PC | LI_COEF_PC_CH | LI_COEF_PC_PC) : (LI_COEF_PC_CH | LI_COEF_PC_PC)) &
							      ((li_config_table[j].send_pc.card_address.low | li_config_table[j].send_pc.card_address.high) ?
							       (LI_COEF_CH_CH | LI_COEF_CH_PC | LI_COEF_PC_CH | LI_COEF_PC_PC) : (LI_COEF_CH_CH | LI_COEF_CH_PC))))));
				}
			} while ((j < li_total_channels)
				 && ((p - plci->internal_req_buffer) + 16 < INTERNAL_REQ_BUFFER_SIZE));
		}
		else if (j == li_total_channels)
		{
			plci->internal_command = plci->li_write_command;
			if (plci_nl_busy(plci))
				return (true);
			if (a->li_pri)
			{
				*(p++) = UDATA_REQUEST_SET_MIXER_COEFS_PRI_SYNC;
				w = 0;
				if (li_config_table[i].channel & LI_CHANNEL_TX_DATA)
					w |= MIXER_FEATURE_ENABLE_TX_DATA;
				if (li_config_table[i].channel & LI_CHANNEL_RX_DATA)
					w |= MIXER_FEATURE_ENABLE_RX_DATA;
				*(p++) = (byte) w;
				*(p++) = (byte)(w >> 8);
			}
			else
			{
				*(p++) = UDATA_REQUEST_SET_MIXER_COEFS_BRI;
				w = 0;
				if ((plci->tel == ADV_VOICE) && (plci == a->AdvSignalPLCI)
				    && (ADV_VOICE_NEW_COEF_BASE + sizeof(word) <= a->adv_voice_coef_length))
				{
					w = GET_WORD(a->adv_voice_coef_buffer + ADV_VOICE_NEW_COEF_BASE);
				}
				if (li_config_table[i].channel & LI_CHANNEL_TX_DATA)
					w |= MIXER_FEATURE_ENABLE_TX_DATA;
				if (li_config_table[i].channel & LI_CHANNEL_RX_DATA)
					w |= MIXER_FEATURE_ENABLE_RX_DATA;
				*(p++) = (byte) w;
				*(p++) = (byte)(w >> 8);
				for (j = 0; j < sizeof(ch_map); j += 2)
				{
					if (plci->li_bchannel_id == 2)
					{
						ch_map[j] = (byte)(j + 1);
						ch_map[j + 1] = (byte) j;
					}
					else
					{
						ch_map[j] = (byte) j;
						ch_map[j + 1] = (byte)(j + 1);
					}
				}
				for (n = 0; n < ARRAY_SIZE(mixer_write_prog_bri); n++)
				{
					i = a->li_base + ch_map[mixer_write_prog_bri[n].to_ch];
					j = a->li_base + ch_map[mixer_write_prog_bri[n].from_ch];
					if (li_config_table[i].channel & li_config_table[j].channel & LI_CHANNEL_INVOLVED)
					{
						*p = (mixer_write_prog_bri[n].xconnect_override != 0) ?
							mixer_write_prog_bri[n].xconnect_override :
							((li_config_table[i].coef_table[j] & mixer_write_prog_bri[n].mask) ? 0x80 : 0x01);
						if ((i >= a->li_base + MIXER_BCHANNELS_BRI) || (j >= a->li_base + MIXER_BCHANNELS_BRI))
						{
							w = ((li_config_table[i].coef_table[j] & 0xf) ^ (li_config_table[i].coef_table[j] >> 4));
							li_config_table[i].coef_table[j] ^= (w & mixer_write_prog_bri[n].mask) << 4;
						}
					}
					else
					{
						*p = 0x00;
						if ((a->AdvSignalPLCI != NULL) && (a->AdvSignalPLCI->tel == ADV_VOICE))
						{
							w = (plci == a->AdvSignalPLCI) ? n : mixer_swapped_index_bri[n];
							if (ADV_VOICE_NEW_COEF_BASE + sizeof(word) + w < a->adv_voice_coef_length)
								*p = a->adv_voice_coef_buffer[ADV_VOICE_NEW_COEF_BASE + sizeof(word) + w];
						}
					}
					p++;
				}
			}
			j = li_total_channels + 1;
		}
	}
	else
	{
		if (j <= li_total_channels)
		{
			plci->internal_command = plci->li_write_command;
			if (plci_nl_busy(plci))
				return (true);
			if (j < a->li_base)
				j = a->li_base;
			if (a->li_pri)
			{
				*(p++) = UDATA_REQUEST_SET_MIXER_COEFS_PRI_SYNC;
				w = 0;
				if (li_config_table[i].channel & LI_CHANNEL_TX_DATA)
					w |= MIXER_FEATURE_ENABLE_TX_DATA;
				if (li_config_table[i].channel & LI_CHANNEL_RX_DATA)
					w |= MIXER_FEATURE_ENABLE_RX_DATA;
				*(p++) = (byte) w;
				*(p++) = (byte)(w >> 8);
				for (n = 0; n < ARRAY_SIZE(mixer_write_prog_pri); n++)
				{
					*(p++) = (byte)((plci->li_bchannel_id - 1) | mixer_write_prog_pri[n].line_flags);
					for (j = a->li_base; j < a->li_base + MIXER_CHANNELS_PRI; j++)
					{
						w = ((li_config_table[i].coef_table[j] & 0xf) ^ (li_config_table[i].coef_table[j] >> 4));
						if (w & mixer_write_prog_pri[n].mask)
						{
							*(p++) = (li_config_table[i].coef_table[j] & mixer_write_prog_pri[n].mask) ? 0x80 : 0x01;
							li_config_table[i].coef_table[j] ^= mixer_write_prog_pri[n].mask << 4;
						}
						else
							*(p++) = 0x00;
					}
					*(p++) = (byte)((plci->li_bchannel_id - 1) | MIXER_COEF_LINE_ROW_FLAG | mixer_write_prog_pri[n].line_flags);
					for (j = a->li_base; j < a->li_base + MIXER_CHANNELS_PRI; j++)
					{
						w = ((li_config_table[j].coef_table[i] & 0xf) ^ (li_config_table[j].coef_table[i] >> 4));
						if (w & mixer_write_prog_pri[n].mask)
						{
							*(p++) = (li_config_table[j].coef_table[i] & mixer_write_prog_pri[n].mask) ? 0x80 : 0x01;
							li_config_table[j].coef_table[i] ^= mixer_write_prog_pri[n].mask << 4;
						}
						else
							*(p++) = 0x00;
					}
				}
			}
			else
			{
				*(p++) = UDATA_REQUEST_SET_MIXER_COEFS_BRI;
				w = 0;
				if ((plci->tel == ADV_VOICE) && (plci == a->AdvSignalPLCI)
				    && (ADV_VOICE_NEW_COEF_BASE + sizeof(word) <= a->adv_voice_coef_length))
				{
					w = GET_WORD(a->adv_voice_coef_buffer + ADV_VOICE_NEW_COEF_BASE);
				}
				if (li_config_table[i].channel & LI_CHANNEL_TX_DATA)
					w |= MIXER_FEATURE_ENABLE_TX_DATA;
				if (li_config_table[i].channel & LI_CHANNEL_RX_DATA)
					w |= MIXER_FEATURE_ENABLE_RX_DATA;
				*(p++) = (byte) w;
				*(p++) = (byte)(w >> 8);
				for (j = 0; j < sizeof(ch_map); j += 2)
				{
					if (plci->li_bchannel_id == 2)
					{
						ch_map[j] = (byte)(j + 1);
						ch_map[j + 1] = (byte) j;
					}
					else
					{
						ch_map[j] = (byte) j;
						ch_map[j + 1] = (byte)(j + 1);
					}
				}
				for (n = 0; n < ARRAY_SIZE(mixer_write_prog_bri); n++)
				{
					i = a->li_base + ch_map[mixer_write_prog_bri[n].to_ch];
					j = a->li_base + ch_map[mixer_write_prog_bri[n].from_ch];
					if (li_config_table[i].channel & li_config_table[j].channel & LI_CHANNEL_INVOLVED)
					{
						*p = ((li_config_table[i].coef_table[j] & mixer_write_prog_bri[n].mask) ? 0x80 : 0x01);
						w = ((li_config_table[i].coef_table[j] & 0xf) ^ (li_config_table[i].coef_table[j] >> 4));
						li_config_table[i].coef_table[j] ^= (w & mixer_write_prog_bri[n].mask) << 4;
					}
					else
					{
						*p = 0x00;
						if ((a->AdvSignalPLCI != NULL) && (a->AdvSignalPLCI->tel == ADV_VOICE))
						{
							w = (plci == a->AdvSignalPLCI) ? n : mixer_swapped_index_bri[n];
							if (ADV_VOICE_NEW_COEF_BASE + sizeof(word) + w < a->adv_voice_coef_length)
								*p = a->adv_voice_coef_buffer[ADV_VOICE_NEW_COEF_BASE + sizeof(word) + w];
						}
					}
					p++;
				}
			}
			j = li_total_channels + 1;
		}
	}
	plci->li_write_channel = j;
	if (p != plci->internal_req_buffer)
	{
		plci->NData[0].P = plci->internal_req_buffer;
		plci->NData[0].PLength = p - plci->internal_req_buffer;
		plci->NL.X = plci->NData;
		plci->NL.ReqCh = 0;
		plci->NL.Req = plci->nl_req = (byte) N_UDATA;
		plci->adapter->request(&plci->NL);
	}
	return (true);
}