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
struct ieee80211_ccmp_data {int key_idx; int key_set; int dot11RSNAStatsCCMPFormatErrors; int dot11RSNAStatsCCMPReplays; int dot11RSNAStatsCCMPDecryptErrors; int /*<<< orphan*/  rx_pn; int /*<<< orphan*/  tx_pn; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static char *ieee80211_ccmp_print_stats(char *p, void *priv)
{
	struct ieee80211_ccmp_data *ccmp = priv;

	p += sprintf(p, "key[%d] alg=CCMP key_set=%d tx_pn=%pm rx_pn=%pm format_errors=%d replays=%d decrypt_errors=%d\n",
		     ccmp->key_idx, ccmp->key_set,
		     ccmp->tx_pn, ccmp->rx_pn,
		     ccmp->dot11RSNAStatsCCMPFormatErrors,
		     ccmp->dot11RSNAStatsCCMPReplays,
		     ccmp->dot11RSNAStatsCCMPDecryptErrors);

	return p;
}