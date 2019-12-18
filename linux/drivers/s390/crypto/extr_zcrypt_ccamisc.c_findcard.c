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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct zcrypt_device_status_ext {int functions; int /*<<< orphan*/  qid; scalar_t__ online; } ;
struct cca_info {int hwtype; char cur_mk_state; scalar_t__ cur_mkvp; char old_mk_state; scalar_t__ old_mkvp; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_QID_CARD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AP_QID_QUEUE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_ZDEV_ENTRIES_EXT ; 
 scalar_t__ cca_info_cache_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cca_info*) ; 
 int /*<<< orphan*/  cca_info_cache_scrub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cca_info_cache_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cca_info*) ; 
 scalar_t__ fetch_cca_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cca_info*) ; 
 int /*<<< orphan*/  kfree (struct zcrypt_device_status_ext*) ; 
 struct zcrypt_device_status_ext* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcrypt_device_status_mask_ext (struct zcrypt_device_status_ext*) ; 

__attribute__((used)) static int findcard(u64 mkvp, u16 *pcardnr, u16 *pdomain,
		    int verify, int minhwtype)
{
	struct zcrypt_device_status_ext *device_status;
	u16 card, dom;
	struct cca_info ci;
	int i, rc, oi = -1;

	/* mkvp must not be zero, minhwtype needs to be >= 0 */
	if (mkvp == 0 || minhwtype < 0)
		return -EINVAL;

	/* fetch status of all crypto cards */
	device_status = kmalloc_array(MAX_ZDEV_ENTRIES_EXT,
				      sizeof(struct zcrypt_device_status_ext),
				      GFP_KERNEL);
	if (!device_status)
		return -ENOMEM;
	zcrypt_device_status_mask_ext(device_status);

	/* walk through all crypto cards */
	for (i = 0; i < MAX_ZDEV_ENTRIES_EXT; i++) {
		card = AP_QID_CARD(device_status[i].qid);
		dom = AP_QID_QUEUE(device_status[i].qid);
		if (device_status[i].online &&
		    device_status[i].functions & 0x04) {
			/* enabled CCA card, check current mkvp from cache */
			if (cca_info_cache_fetch(card, dom, &ci) == 0 &&
			    ci.hwtype >= minhwtype &&
			    ci.cur_mk_state == '2' &&
			    ci.cur_mkvp == mkvp) {
				if (!verify)
					break;
				/* verify: refresh card info */
				if (fetch_cca_info(card, dom, &ci) == 0) {
					cca_info_cache_update(card, dom, &ci);
					if (ci.hwtype >= minhwtype &&
					    ci.cur_mk_state == '2' &&
					    ci.cur_mkvp == mkvp)
						break;
				}
			}
		} else {
			/* Card is offline and/or not a CCA card. */
			/* del mkvp entry from cache if it exists */
			cca_info_cache_scrub(card, dom);
		}
	}
	if (i >= MAX_ZDEV_ENTRIES_EXT) {
		/* nothing found, so this time without cache */
		for (i = 0; i < MAX_ZDEV_ENTRIES_EXT; i++) {
			if (!(device_status[i].online &&
			      device_status[i].functions & 0x04))
				continue;
			card = AP_QID_CARD(device_status[i].qid);
			dom = AP_QID_QUEUE(device_status[i].qid);
			/* fresh fetch mkvp from adapter */
			if (fetch_cca_info(card, dom, &ci) == 0) {
				cca_info_cache_update(card, dom, &ci);
				if (ci.hwtype >= minhwtype &&
				    ci.cur_mk_state == '2' &&
				    ci.cur_mkvp == mkvp)
					break;
				if (ci.hwtype >= minhwtype &&
				    ci.old_mk_state == '2' &&
				    ci.old_mkvp == mkvp &&
				    oi < 0)
					oi = i;
			}
		}
		if (i >= MAX_ZDEV_ENTRIES_EXT && oi >= 0) {
			/* old mkvp matched, use this card then */
			card = AP_QID_CARD(device_status[oi].qid);
			dom = AP_QID_QUEUE(device_status[oi].qid);
		}
	}
	if (i < MAX_ZDEV_ENTRIES_EXT || oi >= 0) {
		if (pcardnr)
			*pcardnr = card;
		if (pdomain)
			*pdomain = dom;
		rc = (i < MAX_ZDEV_ENTRIES_EXT ? 0 : 1);
	} else
		rc = -ENODEV;

	kfree(device_status);
	return rc;
}