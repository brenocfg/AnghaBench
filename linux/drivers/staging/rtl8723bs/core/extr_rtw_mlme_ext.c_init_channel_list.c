#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct p2p_reg_class {size_t channels; scalar_t__* channel; scalar_t__ reg_class; } ;
struct p2p_oper_class_map {int member_0; int member_1; int member_2; int member_3; int member_4; scalar_t__ member_5; scalar_t__ min_chan; scalar_t__ max_chan; int inc; scalar_t__ bw; scalar_t__ op_class; } ;
struct p2p_channels {int reg_classes; struct p2p_reg_class* reg_class; } ;
struct TYPE_2__ {scalar_t__ ht_enable; int bw_mode; } ;
struct adapter {TYPE_1__ registrypriv; } ;
typedef  int /*<<< orphan*/  RT_CHANNEL_INFO ;

/* Variables and functions */
 scalar_t__ BW20 ; 
 scalar_t__ BW40MINUS ; 
 scalar_t__ BW40PLUS ; 
 int IEEE80211A ; 
 int IEEE80211G ; 
 int /*<<< orphan*/  has_channel (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void init_channel_list(struct adapter *padapter, RT_CHANNEL_INFO *channel_set,
							  u8 chanset_size,
							  struct p2p_channels *channel_list)
{

	struct p2p_oper_class_map op_class[] = {
		{ IEEE80211G,  81,   1,  13,  1, BW20 },
		{ IEEE80211G,  82,  14,  14,  1, BW20 },
		{ IEEE80211A, 115,  36,  48,  4, BW20 },
		{ IEEE80211A, 116,  36,  44,  8, BW40PLUS },
		{ IEEE80211A, 117,  40,  48,  8, BW40MINUS },
		{ IEEE80211A, 124, 149, 161,  4, BW20 },
		{ IEEE80211A, 125, 149, 169,  4, BW20 },
		{ IEEE80211A, 126, 149, 157,  8, BW40PLUS },
		{ IEEE80211A, 127, 153, 161,  8, BW40MINUS },
		{ -1, 0, 0, 0, 0, BW20 }
	};

	int cla, op;

	cla = 0;

	for (op = 0; op_class[op].op_class; op++) {
		u8 ch;
		struct p2p_oper_class_map *o = &op_class[op];
		struct p2p_reg_class *reg = NULL;

		for (ch = o->min_chan; ch <= o->max_chan; ch += o->inc) {
			if (!has_channel(channel_set, chanset_size, ch))
				continue;

			if ((0 == padapter->registrypriv.ht_enable) && (8 == o->inc))
				continue;

			if ((0 < (padapter->registrypriv.bw_mode & 0xf0)) &&
				((BW40MINUS == o->bw) || (BW40PLUS == o->bw)))
				continue;

			if (!reg) {
				reg = &channel_list->reg_class[cla];
				cla++;
				reg->reg_class = o->op_class;
				reg->channels = 0;
			}
			reg->channel[reg->channels] = ch;
			reg->channels++;
		}
	}
	channel_list->reg_classes = cla;

}