#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int length; } ;
union iwreq_data {TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct libipw_geo {int bg_channels; int a_channels; TYPE_6__* a; TYPE_5__* bg; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_11__ {int qual; int updated; scalar_t__ noise; scalar_t__ level; } ;
struct TYPE_10__ {int qual; int updated; scalar_t__ noise; scalar_t__ level; } ;
struct iw_range {int throughput; int num_bitrates; int* bitrate; int* encoding_size; int num_encoding_sizes; int we_version_source; int num_channels; int num_frequency; int* event_capa; int enc_capa; int scan_capa; TYPE_7__* freq; int /*<<< orphan*/  we_version_compiled; int /*<<< orphan*/  max_encoding_tokens; int /*<<< orphan*/  max_frag; int /*<<< orphan*/  min_frag; int /*<<< orphan*/  max_rts; TYPE_3__ avg_qual; TYPE_2__ max_qual; } ;
struct TYPE_12__ {int* supported_rates; int /*<<< orphan*/  num_rates; } ;
struct ipw_priv {int /*<<< orphan*/  mutex; TYPE_8__* ieee; TYPE_4__ rates; } ;
struct TYPE_16__ {int mode; scalar_t__ iw_mode; } ;
struct TYPE_15__ {int m; int e; int /*<<< orphan*/  i; } ;
struct TYPE_14__ {int flags; int freq; int /*<<< orphan*/  channel; } ;
struct TYPE_13__ {int flags; int freq; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_RTS_THRESHOLD ; 
 int IEEE_A ; 
 int IEEE_B ; 
 int IEEE_G ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*) ; 
 int IW_ENC_CAPA_CIPHER_CCMP ; 
 int IW_ENC_CAPA_CIPHER_TKIP ; 
 int IW_ENC_CAPA_WPA ; 
 int IW_ENC_CAPA_WPA2 ; 
 int IW_EVENT_CAPA_K_0 ; 
 int IW_EVENT_CAPA_K_1 ; 
 int IW_EVENT_CAPA_MASK (int /*<<< orphan*/ ) ; 
 scalar_t__ IW_MAX_BITRATES ; 
 int IW_MAX_FREQUENCIES ; 
 scalar_t__ IW_MODE_ADHOC ; 
 int IW_SCAN_CAPA_ESSID ; 
 int IW_SCAN_CAPA_TYPE ; 
 int LIBIPW_CH_PASSIVE_ONLY ; 
 int /*<<< orphan*/  MAX_FRAG_THRESHOLD ; 
 int /*<<< orphan*/  MIN_FRAG_THRESHOLD ; 
 int /*<<< orphan*/  SIOCGIWAP ; 
 int /*<<< orphan*/  SIOCGIWSCAN ; 
 int /*<<< orphan*/  SIOCGIWTHRSPY ; 
 int /*<<< orphan*/  WEP_KEYS ; 
 int /*<<< orphan*/  WIRELESS_EXT ; 
 struct libipw_geo* libipw_get_geo (TYPE_8__*) ; 
 struct ipw_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  memset (struct iw_range*,int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw_wx_get_range(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu, char *extra)
{
	struct ipw_priv *priv = libipw_priv(dev);
	struct iw_range *range = (struct iw_range *)extra;
	const struct libipw_geo *geo = libipw_get_geo(priv->ieee);
	int i = 0, j;

	wrqu->data.length = sizeof(*range);
	memset(range, 0, sizeof(*range));

	/* 54Mbs == ~27 Mb/s real (802.11g) */
	range->throughput = 27 * 1000 * 1000;

	range->max_qual.qual = 100;
	/* TODO: Find real max RSSI and stick here */
	range->max_qual.level = 0;
	range->max_qual.noise = 0;
	range->max_qual.updated = 7;	/* Updated all three */

	range->avg_qual.qual = 70;
	/* TODO: Find real 'good' to 'bad' threshold value for RSSI */
	range->avg_qual.level = 0;	/* FIXME to real average level */
	range->avg_qual.noise = 0;
	range->avg_qual.updated = 7;	/* Updated all three */
	mutex_lock(&priv->mutex);
	range->num_bitrates = min(priv->rates.num_rates, (u8) IW_MAX_BITRATES);

	for (i = 0; i < range->num_bitrates; i++)
		range->bitrate[i] = (priv->rates.supported_rates[i] & 0x7F) *
		    500000;

	range->max_rts = DEFAULT_RTS_THRESHOLD;
	range->min_frag = MIN_FRAG_THRESHOLD;
	range->max_frag = MAX_FRAG_THRESHOLD;

	range->encoding_size[0] = 5;
	range->encoding_size[1] = 13;
	range->num_encoding_sizes = 2;
	range->max_encoding_tokens = WEP_KEYS;

	/* Set the Wireless Extension versions */
	range->we_version_compiled = WIRELESS_EXT;
	range->we_version_source = 18;

	i = 0;
	if (priv->ieee->mode & (IEEE_B | IEEE_G)) {
		for (j = 0; j < geo->bg_channels && i < IW_MAX_FREQUENCIES; j++) {
			if ((priv->ieee->iw_mode == IW_MODE_ADHOC) &&
			    (geo->bg[j].flags & LIBIPW_CH_PASSIVE_ONLY))
				continue;

			range->freq[i].i = geo->bg[j].channel;
			range->freq[i].m = geo->bg[j].freq * 100000;
			range->freq[i].e = 1;
			i++;
		}
	}

	if (priv->ieee->mode & IEEE_A) {
		for (j = 0; j < geo->a_channels && i < IW_MAX_FREQUENCIES; j++) {
			if ((priv->ieee->iw_mode == IW_MODE_ADHOC) &&
			    (geo->a[j].flags & LIBIPW_CH_PASSIVE_ONLY))
				continue;

			range->freq[i].i = geo->a[j].channel;
			range->freq[i].m = geo->a[j].freq * 100000;
			range->freq[i].e = 1;
			i++;
		}
	}

	range->num_channels = i;
	range->num_frequency = i;

	mutex_unlock(&priv->mutex);

	/* Event capability (kernel + driver) */
	range->event_capa[0] = (IW_EVENT_CAPA_K_0 |
				IW_EVENT_CAPA_MASK(SIOCGIWTHRSPY) |
				IW_EVENT_CAPA_MASK(SIOCGIWAP) |
				IW_EVENT_CAPA_MASK(SIOCGIWSCAN));
	range->event_capa[1] = IW_EVENT_CAPA_K_1;

	range->enc_capa = IW_ENC_CAPA_WPA | IW_ENC_CAPA_WPA2 |
		IW_ENC_CAPA_CIPHER_TKIP | IW_ENC_CAPA_CIPHER_CCMP;

	range->scan_capa = IW_SCAN_CAPA_ESSID | IW_SCAN_CAPA_TYPE;

	IPW_DEBUG_WX("GET Range\n");
	return 0;
}