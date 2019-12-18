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
struct sta_info {int /*<<< orphan*/  users; struct lib80211_crypt_data* crypt; } ;
struct lib80211_crypt_data {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr2; } ;
struct TYPE_4__ {TYPE_3__* ap; } ;
typedef  TYPE_1__ local_info_t ;
struct TYPE_5__ {int /*<<< orphan*/  sta_table_lock; } ;

/* Variables and functions */
 struct sta_info* ap_get_sta (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int hostap_handle_sta_crypto(local_info_t *local,
			     struct ieee80211_hdr *hdr,
			     struct lib80211_crypt_data **crypt,
			     void **sta_ptr)
{
	struct sta_info *sta;

	spin_lock(&local->ap->sta_table_lock);
	sta = ap_get_sta(local->ap, hdr->addr2);
	if (sta)
		atomic_inc(&sta->users);
	spin_unlock(&local->ap->sta_table_lock);

	if (!sta)
		return -1;

	if (sta->crypt) {
		*crypt = sta->crypt;
		*sta_ptr = sta;
		/* hostap_handle_sta_release() will be called to release STA
		 * info */
	} else
		atomic_dec(&sta->users);

	return 0;
}