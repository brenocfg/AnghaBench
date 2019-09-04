#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  int /*<<< orphan*/  dword ;
typedef  int /*<<< orphan*/  ch_map ;
typedef  int byte ;
struct TYPE_14__ {int* flag_table; int curchnl; int channel; int* coef_table; TYPE_1__* plci; } ;
struct TYPE_13__ {size_t to_ch; size_t from_ch; int mask; } ;
struct TYPE_12__ {int adv_voice_coef_length; int* adv_voice_coef_buffer; size_t li_base; int manufacturer_features; int /*<<< orphan*/  li_pri; int /*<<< orphan*/  Id; } ;
struct TYPE_11__ {int Id; int li_bchannel_id; int B1_facilities; TYPE_2__* adapter; } ;
typedef  TYPE_1__ PLCI ;
typedef  TYPE_2__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  ADV_VOICE_COEF_BUFFER_SIZE ; 
 int ADV_VOICE_NEW_COEF_BASE ; 
 int ADV_VOICE_OLD_COEF_COUNT ; 
#define  ADV_VOICE_WRITE_ACTIVATION 129 
#define  ADV_VOICE_WRITE_DEACTIVATION 128 
 int ARRAY_SIZE (TYPE_5__*) ; 
 int B1_FACILITY_MIXER ; 
 int /*<<< orphan*/  DSP_CTRL_OLD_SET_MIXER_COEFFICIENTS ; 
 scalar_t__ FILE_ ; 
 int /*<<< orphan*/  FTY ; 
 int GET_WORD (int*) ; 
 int LI_CHANNEL_INVOLVED ; 
 int LI_CHANNEL_RX_DATA ; 
 int LI_CHANNEL_TX_DATA ; 
 int LI_FLAG_CONFERENCE ; 
 int LI_FLAG_MIX ; 
 int LI_FLAG_MONITOR ; 
 int MANUFACTURER_FEATURE_SLAVE_CODEC ; 
 int MIXER_CHANNELS_BRI ; 
 int MIXER_FEATURE_ENABLE_RX_DATA ; 
 int MIXER_FEATURE_ENABLE_TX_DATA ; 
 int /*<<< orphan*/  MIXER_IC_CHANNEL_BASE ; 
 int /*<<< orphan*/  PUT_WORD (int*,int) ; 
 int /*<<< orphan*/  TEL_CTRL ; 
 int UnMapController (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_p (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,int) ; 
 TYPE_7__* li_config_table ; 
 int li_total_channels ; 
 int /*<<< orphan*/  mixer_calculate_coefs (TYPE_2__*) ; 
 TYPE_5__* mixer_write_prog_bri ; 
 int /*<<< orphan*/  send_req (TYPE_1__*) ; 
 int /*<<< orphan*/  sig_req (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adv_voice_write_coefs(PLCI *plci, word write_command)
{
	DIVA_CAPI_ADAPTER *a;
	word i;
	byte *p;

	word w, n, j, k;
	byte ch_map[MIXER_CHANNELS_BRI];

	byte coef_buffer[ADV_VOICE_COEF_BUFFER_SIZE + 2];

	dbug(1, dprintf("[%06lx] %s,%d: adv_voice_write_coefs %d",
			(dword)((plci->Id << 8) | UnMapController(plci->adapter->Id)),
			(char *)(FILE_), __LINE__, write_command));

	a = plci->adapter;
	p = coef_buffer + 1;
	*(p++) = DSP_CTRL_OLD_SET_MIXER_COEFFICIENTS;
	i = 0;
	while (i + sizeof(word) <= a->adv_voice_coef_length)
	{
		PUT_WORD(p, GET_WORD(a->adv_voice_coef_buffer + i));
		p += 2;
		i += 2;
	}
	while (i < ADV_VOICE_OLD_COEF_COUNT * sizeof(word))
	{
		PUT_WORD(p, 0x8000);
		p += 2;
		i += 2;
	}

	if (!a->li_pri && (plci->li_bchannel_id == 0))
	{
		if ((li_config_table[a->li_base].plci == NULL) && (li_config_table[a->li_base + 1].plci != NULL))
		{
			plci->li_bchannel_id = 1;
			li_config_table[a->li_base].plci = plci;
			dbug(1, dprintf("[%06lx] %s,%d: adv_voice_set_bchannel_id %d",
					(dword)((plci->Id << 8) | UnMapController(plci->adapter->Id)),
					(char *)(FILE_), __LINE__, plci->li_bchannel_id));
		}
		else if ((li_config_table[a->li_base].plci != NULL) && (li_config_table[a->li_base + 1].plci == NULL))
		{
			plci->li_bchannel_id = 2;
			li_config_table[a->li_base + 1].plci = plci;
			dbug(1, dprintf("[%06lx] %s,%d: adv_voice_set_bchannel_id %d",
					(dword)((plci->Id << 8) | UnMapController(plci->adapter->Id)),
					(char *)(FILE_), __LINE__, plci->li_bchannel_id));
		}
	}
	if (!a->li_pri && (plci->li_bchannel_id != 0)
	    && (li_config_table[a->li_base + (plci->li_bchannel_id - 1)].plci == plci))
	{
		i = a->li_base + (plci->li_bchannel_id - 1);
		switch (write_command)
		{
		case ADV_VOICE_WRITE_ACTIVATION:
			j = a->li_base + MIXER_IC_CHANNEL_BASE + (plci->li_bchannel_id - 1);
			k = a->li_base + MIXER_IC_CHANNEL_BASE + (2 - plci->li_bchannel_id);
			if (!(plci->B1_facilities & B1_FACILITY_MIXER))
			{
				li_config_table[j].flag_table[i] |= LI_FLAG_CONFERENCE | LI_FLAG_MIX;
				li_config_table[i].flag_table[j] |= LI_FLAG_CONFERENCE | LI_FLAG_MONITOR;
			}
			if (a->manufacturer_features & MANUFACTURER_FEATURE_SLAVE_CODEC)
			{
				li_config_table[k].flag_table[i] |= LI_FLAG_CONFERENCE | LI_FLAG_MIX;
				li_config_table[i].flag_table[k] |= LI_FLAG_CONFERENCE | LI_FLAG_MONITOR;
				li_config_table[k].flag_table[j] |= LI_FLAG_CONFERENCE;
				li_config_table[j].flag_table[k] |= LI_FLAG_CONFERENCE;
			}
			mixer_calculate_coefs(a);
			li_config_table[i].curchnl = li_config_table[i].channel;
			li_config_table[j].curchnl = li_config_table[j].channel;
			if (a->manufacturer_features & MANUFACTURER_FEATURE_SLAVE_CODEC)
				li_config_table[k].curchnl = li_config_table[k].channel;
			break;

		case ADV_VOICE_WRITE_DEACTIVATION:
			for (j = 0; j < li_total_channels; j++)
			{
				li_config_table[i].flag_table[j] = 0;
				li_config_table[j].flag_table[i] = 0;
			}
			k = a->li_base + MIXER_IC_CHANNEL_BASE + (plci->li_bchannel_id - 1);
			for (j = 0; j < li_total_channels; j++)
			{
				li_config_table[k].flag_table[j] = 0;
				li_config_table[j].flag_table[k] = 0;
			}
			if (a->manufacturer_features & MANUFACTURER_FEATURE_SLAVE_CODEC)
			{
				k = a->li_base + MIXER_IC_CHANNEL_BASE + (2 - plci->li_bchannel_id);
				for (j = 0; j < li_total_channels; j++)
				{
					li_config_table[k].flag_table[j] = 0;
					li_config_table[j].flag_table[k] = 0;
				}
			}
			mixer_calculate_coefs(a);
			break;
		}
		if (plci->B1_facilities & B1_FACILITY_MIXER)
		{
			w = 0;
			if (ADV_VOICE_NEW_COEF_BASE + sizeof(word) <= a->adv_voice_coef_length)
				w = GET_WORD(a->adv_voice_coef_buffer + ADV_VOICE_NEW_COEF_BASE);
			if (li_config_table[i].channel & LI_CHANNEL_TX_DATA)
				w |= MIXER_FEATURE_ENABLE_TX_DATA;
			if (li_config_table[i].channel & LI_CHANNEL_RX_DATA)
				w |= MIXER_FEATURE_ENABLE_RX_DATA;
			*(p++) = (byte) w;
			*(p++) = (byte)(w >> 8);
			for (j = 0; j < sizeof(ch_map); j += 2)
			{
				ch_map[j] = (byte)(j + (plci->li_bchannel_id - 1));
				ch_map[j + 1] = (byte)(j + (2 - plci->li_bchannel_id));
			}
			for (n = 0; n < ARRAY_SIZE(mixer_write_prog_bri); n++)
			{
				i = a->li_base + ch_map[mixer_write_prog_bri[n].to_ch];
				j = a->li_base + ch_map[mixer_write_prog_bri[n].from_ch];
				if (li_config_table[i].channel & li_config_table[j].channel & LI_CHANNEL_INVOLVED)
				{
					*(p++) = ((li_config_table[i].coef_table[j] & mixer_write_prog_bri[n].mask) ? 0x80 : 0x01);
					w = ((li_config_table[i].coef_table[j] & 0xf) ^ (li_config_table[i].coef_table[j] >> 4));
					li_config_table[i].coef_table[j] ^= (w & mixer_write_prog_bri[n].mask) << 4;
				}
				else
				{
					*(p++) = (ADV_VOICE_NEW_COEF_BASE + sizeof(word) + n < a->adv_voice_coef_length) ?
						a->adv_voice_coef_buffer[ADV_VOICE_NEW_COEF_BASE + sizeof(word) + n] : 0x00;
				}
			}
		}
		else
		{
			for (i = ADV_VOICE_NEW_COEF_BASE; i < a->adv_voice_coef_length; i++)
				*(p++) = a->adv_voice_coef_buffer[i];
		}
	}
	else

	{
		for (i = ADV_VOICE_NEW_COEF_BASE; i < a->adv_voice_coef_length; i++)
			*(p++) = a->adv_voice_coef_buffer[i];
	}
	coef_buffer[0] = (p - coef_buffer) - 1;
	add_p(plci, FTY, coef_buffer);
	sig_req(plci, TEL_CTRL, 0);
	send_req(plci);
}