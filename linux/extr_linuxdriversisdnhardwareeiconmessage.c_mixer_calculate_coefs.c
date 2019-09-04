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
typedef  int /*<<< orphan*/  dword ;
struct TYPE_5__ {int channel; int chflags; scalar_t__* flag_table; int* coef_table; int curchnl; } ;
struct TYPE_4__ {int /*<<< orphan*/  Id; } ;
typedef  TYPE_1__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
 scalar_t__ FILE_ ; 
 int LI_CHANNEL_ACTIVE ; 
 int LI_CHANNEL_ADDRESSES_SET ; 
 int LI_CHANNEL_CONFERENCE ; 
 int LI_CHANNEL_INVOLVED ; 
 int LI_CHANNEL_RX_DATA ; 
 int LI_CHANNEL_TX_DATA ; 
 int LI_CHFLAG_LOOP ; 
 int LI_CHFLAG_MIX ; 
 int LI_CHFLAG_MONITOR ; 
 int LI_COEF_CH_CH ; 
 int LI_COEF_CH_PC ; 
 int LI_COEF_PC_CH ; 
 int LI_COEF_PC_PC ; 
 int LI_FLAG_ANNOUNCEMENT ; 
 int LI_FLAG_CONFERENCE ; 
 int LI_FLAG_INTERCONNECT ; 
 int LI_FLAG_MIX ; 
 int LI_FLAG_MONITOR ; 
 int LI_FLAG_PCCONNECT ; 
 int MIXER_MAX_DUMP_CHANNELS ; 
 scalar_t__ UnMapController (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,...) ; 
 char* hex_byte_pack (char*,int) ; 
 TYPE_3__* li_config_table ; 
 size_t li_total_channels ; 

__attribute__((used)) static void mixer_calculate_coefs(DIVA_CAPI_ADAPTER *a)
{
	word n, i, j;
	char *p;
	char hex_line[2 * MIXER_MAX_DUMP_CHANNELS + MIXER_MAX_DUMP_CHANNELS / 8 + 4];

	dbug(1, dprintf("[%06lx] %s,%d: mixer_calculate_coefs",
			(dword)(UnMapController(a->Id)), (char *)(FILE_), __LINE__));

	for (i = 0; i < li_total_channels; i++)
	{
		li_config_table[i].channel &= LI_CHANNEL_ADDRESSES_SET;
		if (li_config_table[i].chflags != 0)
			li_config_table[i].channel |= LI_CHANNEL_INVOLVED;
		else
		{
			for (j = 0; j < li_total_channels; j++)
			{
				if (((li_config_table[i].flag_table[j]) != 0)
				    || ((li_config_table[j].flag_table[i]) != 0))
				{
					li_config_table[i].channel |= LI_CHANNEL_INVOLVED;
				}
				if (((li_config_table[i].flag_table[j] & LI_FLAG_CONFERENCE) != 0)
				    || ((li_config_table[j].flag_table[i] & LI_FLAG_CONFERENCE) != 0))
				{
					li_config_table[i].channel |= LI_CHANNEL_CONFERENCE;
				}
			}
		}
	}
	for (i = 0; i < li_total_channels; i++)
	{
		for (j = 0; j < li_total_channels; j++)
		{
			li_config_table[i].coef_table[j] &= ~(LI_COEF_CH_CH | LI_COEF_CH_PC | LI_COEF_PC_CH | LI_COEF_PC_PC);
			if (li_config_table[i].flag_table[j] & LI_FLAG_CONFERENCE)
				li_config_table[i].coef_table[j] |= LI_COEF_CH_CH;
		}
	}
	for (n = 0; n < li_total_channels; n++)
	{
		if (li_config_table[n].channel & LI_CHANNEL_CONFERENCE)
		{
			for (i = 0; i < li_total_channels; i++)
			{
				if (li_config_table[i].channel & LI_CHANNEL_CONFERENCE)
				{
					for (j = 0; j < li_total_channels; j++)
					{
						li_config_table[i].coef_table[j] |=
							li_config_table[i].coef_table[n] & li_config_table[n].coef_table[j];
					}
				}
			}
		}
	}
	for (i = 0; i < li_total_channels; i++)
	{
		if (li_config_table[i].channel & LI_CHANNEL_INVOLVED)
		{
			li_config_table[i].coef_table[i] &= ~LI_COEF_CH_CH;
			for (j = 0; j < li_total_channels; j++)
			{
				if (li_config_table[i].coef_table[j] & LI_COEF_CH_CH)
					li_config_table[i].flag_table[j] |= LI_FLAG_CONFERENCE;
			}
			if (li_config_table[i].flag_table[i] & LI_FLAG_CONFERENCE)
				li_config_table[i].coef_table[i] |= LI_COEF_CH_CH;
		}
	}
	for (i = 0; i < li_total_channels; i++)
	{
		if (li_config_table[i].channel & LI_CHANNEL_INVOLVED)
		{
			for (j = 0; j < li_total_channels; j++)
			{
				if (li_config_table[i].flag_table[j] & LI_FLAG_INTERCONNECT)
					li_config_table[i].coef_table[j] |= LI_COEF_CH_CH;
				if (li_config_table[i].flag_table[j] & LI_FLAG_MONITOR)
					li_config_table[i].coef_table[j] |= LI_COEF_CH_PC;
				if (li_config_table[i].flag_table[j] & LI_FLAG_MIX)
					li_config_table[i].coef_table[j] |= LI_COEF_PC_CH;
				if (li_config_table[i].flag_table[j] & LI_FLAG_PCCONNECT)
					li_config_table[i].coef_table[j] |= LI_COEF_PC_PC;
			}
			if (li_config_table[i].chflags & LI_CHFLAG_MONITOR)
			{
				for (j = 0; j < li_total_channels; j++)
				{
					if (li_config_table[i].flag_table[j] & LI_FLAG_INTERCONNECT)
					{
						li_config_table[i].coef_table[j] |= LI_COEF_CH_PC;
						if (li_config_table[j].chflags & LI_CHFLAG_MIX)
							li_config_table[i].coef_table[j] |= LI_COEF_PC_CH | LI_COEF_PC_PC;
					}
				}
			}
			if (li_config_table[i].chflags & LI_CHFLAG_MIX)
			{
				for (j = 0; j < li_total_channels; j++)
				{
					if (li_config_table[j].flag_table[i] & LI_FLAG_INTERCONNECT)
						li_config_table[j].coef_table[i] |= LI_COEF_PC_CH;
				}
			}
			if (li_config_table[i].chflags & LI_CHFLAG_LOOP)
			{
				for (j = 0; j < li_total_channels; j++)
				{
					if (li_config_table[i].flag_table[j] & LI_FLAG_INTERCONNECT)
					{
						for (n = 0; n < li_total_channels; n++)
						{
							if (li_config_table[n].flag_table[i] & LI_FLAG_INTERCONNECT)
							{
								li_config_table[n].coef_table[j] |= LI_COEF_CH_CH;
								if (li_config_table[j].chflags & LI_CHFLAG_MIX)
								{
									li_config_table[n].coef_table[j] |= LI_COEF_PC_CH;
									if (li_config_table[n].chflags & LI_CHFLAG_MONITOR)
										li_config_table[n].coef_table[j] |= LI_COEF_CH_PC | LI_COEF_PC_PC;
								}
								else if (li_config_table[n].chflags & LI_CHFLAG_MONITOR)
									li_config_table[n].coef_table[j] |= LI_COEF_CH_PC;
							}
						}
					}
				}
			}
		}
	}
	for (i = 0; i < li_total_channels; i++)
	{
		if (li_config_table[i].channel & LI_CHANNEL_INVOLVED)
		{
			if (li_config_table[i].chflags & (LI_CHFLAG_MONITOR | LI_CHFLAG_MIX | LI_CHFLAG_LOOP))
				li_config_table[i].channel |= LI_CHANNEL_ACTIVE;
			if (li_config_table[i].chflags & LI_CHFLAG_MONITOR)
				li_config_table[i].channel |= LI_CHANNEL_RX_DATA;
			if (li_config_table[i].chflags & LI_CHFLAG_MIX)
				li_config_table[i].channel |= LI_CHANNEL_TX_DATA;
			for (j = 0; j < li_total_channels; j++)
			{
				if ((li_config_table[i].flag_table[j] &
				     (LI_FLAG_INTERCONNECT | LI_FLAG_PCCONNECT | LI_FLAG_CONFERENCE | LI_FLAG_MONITOR))
				    || (li_config_table[j].flag_table[i] &
					(LI_FLAG_INTERCONNECT | LI_FLAG_PCCONNECT | LI_FLAG_CONFERENCE | LI_FLAG_ANNOUNCEMENT | LI_FLAG_MIX)))
				{
					li_config_table[i].channel |= LI_CHANNEL_ACTIVE;
				}
				if (li_config_table[i].flag_table[j] & (LI_FLAG_PCCONNECT | LI_FLAG_MONITOR))
					li_config_table[i].channel |= LI_CHANNEL_RX_DATA;
				if (li_config_table[j].flag_table[i] & (LI_FLAG_PCCONNECT | LI_FLAG_ANNOUNCEMENT | LI_FLAG_MIX))
					li_config_table[i].channel |= LI_CHANNEL_TX_DATA;
			}
			if (!(li_config_table[i].channel & LI_CHANNEL_ACTIVE))
			{
				li_config_table[i].coef_table[i] |= LI_COEF_PC_CH | LI_COEF_CH_PC;
				li_config_table[i].channel |= LI_CHANNEL_TX_DATA | LI_CHANNEL_RX_DATA;
			}
		}
	}
	for (i = 0; i < li_total_channels; i++)
	{
		if (li_config_table[i].channel & LI_CHANNEL_INVOLVED)
		{
			j = 0;
			while ((j < li_total_channels) && !(li_config_table[i].flag_table[j] & LI_FLAG_ANNOUNCEMENT))
				j++;
			if (j < li_total_channels)
			{
				for (j = 0; j < li_total_channels; j++)
				{
					li_config_table[i].coef_table[j] &= ~(LI_COEF_CH_CH | LI_COEF_PC_CH);
					if (li_config_table[i].flag_table[j] & LI_FLAG_ANNOUNCEMENT)
						li_config_table[i].coef_table[j] |= LI_COEF_PC_CH;
				}
			}
		}
	}
	n = li_total_channels;
	if (n > MIXER_MAX_DUMP_CHANNELS)
		n = MIXER_MAX_DUMP_CHANNELS;

	p = hex_line;
	for (j = 0; j < n; j++)
	{
		if ((j & 0x7) == 0)
			*(p++) = ' ';
		p = hex_byte_pack(p, li_config_table[j].curchnl);
	}
	*p = '\0';
	dbug(1, dprintf("[%06lx] CURRENT %s",
			(dword)(UnMapController(a->Id)), (char *)hex_line));
	p = hex_line;
	for (j = 0; j < n; j++)
	{
		if ((j & 0x7) == 0)
			*(p++) = ' ';
		p = hex_byte_pack(p, li_config_table[j].channel);
	}
	*p = '\0';
	dbug(1, dprintf("[%06lx] CHANNEL %s",
			(dword)(UnMapController(a->Id)), (char *)hex_line));
	p = hex_line;
	for (j = 0; j < n; j++)
	{
		if ((j & 0x7) == 0)
			*(p++) = ' ';
		p = hex_byte_pack(p, li_config_table[j].chflags);
	}
	*p = '\0';
	dbug(1, dprintf("[%06lx] CHFLAG  %s",
			(dword)(UnMapController(a->Id)), (char *)hex_line));
	for (i = 0; i < n; i++)
	{
		p = hex_line;
		for (j = 0; j < n; j++)
		{
			if ((j & 0x7) == 0)
				*(p++) = ' ';
			p = hex_byte_pack(p, li_config_table[i].flag_table[j]);
		}
		*p = '\0';
		dbug(1, dprintf("[%06lx] FLAG[%02x]%s",
				(dword)(UnMapController(a->Id)), i, (char *)hex_line));
	}
	for (i = 0; i < n; i++)
	{
		p = hex_line;
		for (j = 0; j < n; j++)
		{
			if ((j & 0x7) == 0)
				*(p++) = ' ';
			p = hex_byte_pack(p, li_config_table[i].coef_table[j]);
		}
		*p = '\0';
		dbug(1, dprintf("[%06lx] COEF[%02x]%s",
				(dword)(UnMapController(a->Id)), i, (char *)hex_line));
	}
}