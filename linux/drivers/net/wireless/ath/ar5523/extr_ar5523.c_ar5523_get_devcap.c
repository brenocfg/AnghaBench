#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ar5523 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_ANALOG_2GHz_REVISION ; 
 int /*<<< orphan*/  CAP_ANALOG_5GHz_REVISION ; 
 int /*<<< orphan*/  CAP_BURST_SUPPORT ; 
 int /*<<< orphan*/  CAP_CHAN_SPREAD_SUPPORT ; 
 int /*<<< orphan*/  CAP_CHAP_TUNING_SUPPORT ; 
 int /*<<< orphan*/  CAP_CIPHER_AES_CCM ; 
 int /*<<< orphan*/  CAP_CIPHER_TKIP ; 
 int /*<<< orphan*/  CAP_COMPRESS_SUPPORT ; 
 int /*<<< orphan*/  CAP_CONNECTION_ID_MAX ; 
 int /*<<< orphan*/  CAP_DEVICE_TYPE ; 
 int /*<<< orphan*/  CAP_FAST_FRAMES_SUPPORT ; 
 int /*<<< orphan*/  CAP_HIGH_2GHZ_CHAN ; 
 int /*<<< orphan*/  CAP_HIGH_5GHZ_CHAN ; 
 int /*<<< orphan*/  CAP_LOW_2GHZ_CHAN ; 
 int /*<<< orphan*/  CAP_LOW_5GHZ_CHAN ; 
 int /*<<< orphan*/  CAP_MAC_REVISION ; 
 int /*<<< orphan*/  CAP_MAC_VERSION ; 
 int /*<<< orphan*/  CAP_MIC_TKIP ; 
 int /*<<< orphan*/  CAP_PHY_REVISION ; 
 int /*<<< orphan*/  CAP_REG_CAP_BITS ; 
 int /*<<< orphan*/  CAP_REG_DOMAIN ; 
 int /*<<< orphan*/  CAP_TARGET_REVISION ; 
 int /*<<< orphan*/  CAP_TARGET_VERSION ; 
 int /*<<< orphan*/  CAP_TOTAL_QUEUES ; 
 int /*<<< orphan*/  CAP_TURBOG_SUPPORT ; 
 int /*<<< orphan*/  CAP_TURBO_PRIME_SUPPORT ; 
 int /*<<< orphan*/  CAP_TWICE_ANTENNAGAIN_2G ; 
 int /*<<< orphan*/  CAP_TWICE_ANTENNAGAIN_5G ; 
 int /*<<< orphan*/  CAP_WIRELESS_MODES ; 
 int /*<<< orphan*/  CAP_WME_SUPPORT ; 
 int /*<<< orphan*/  GETCAP (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ar5523_get_devcap(struct ar5523 *ar)
{
#define	GETCAP(x) do {				\
	error = ar5523_get_capability(ar, x, &cap);		\
	if (error != 0)					\
		return error;				\
	ar5523_info(ar, "Cap: "			\
	    "%s=0x%08x\n", #x, cap);	\
} while (0)
	int error;
	u32 cap;

	/* collect device capabilities */
	GETCAP(CAP_TARGET_VERSION);
	GETCAP(CAP_TARGET_REVISION);
	GETCAP(CAP_MAC_VERSION);
	GETCAP(CAP_MAC_REVISION);
	GETCAP(CAP_PHY_REVISION);
	GETCAP(CAP_ANALOG_5GHz_REVISION);
	GETCAP(CAP_ANALOG_2GHz_REVISION);

	GETCAP(CAP_REG_DOMAIN);
	GETCAP(CAP_REG_CAP_BITS);
	GETCAP(CAP_WIRELESS_MODES);
	GETCAP(CAP_CHAN_SPREAD_SUPPORT);
	GETCAP(CAP_COMPRESS_SUPPORT);
	GETCAP(CAP_BURST_SUPPORT);
	GETCAP(CAP_FAST_FRAMES_SUPPORT);
	GETCAP(CAP_CHAP_TUNING_SUPPORT);
	GETCAP(CAP_TURBOG_SUPPORT);
	GETCAP(CAP_TURBO_PRIME_SUPPORT);
	GETCAP(CAP_DEVICE_TYPE);
	GETCAP(CAP_WME_SUPPORT);
	GETCAP(CAP_TOTAL_QUEUES);
	GETCAP(CAP_CONNECTION_ID_MAX);

	GETCAP(CAP_LOW_5GHZ_CHAN);
	GETCAP(CAP_HIGH_5GHZ_CHAN);
	GETCAP(CAP_LOW_2GHZ_CHAN);
	GETCAP(CAP_HIGH_2GHZ_CHAN);
	GETCAP(CAP_TWICE_ANTENNAGAIN_5G);
	GETCAP(CAP_TWICE_ANTENNAGAIN_2G);

	GETCAP(CAP_CIPHER_AES_CCM);
	GETCAP(CAP_CIPHER_TKIP);
	GETCAP(CAP_MIC_TKIP);
	return 0;
}