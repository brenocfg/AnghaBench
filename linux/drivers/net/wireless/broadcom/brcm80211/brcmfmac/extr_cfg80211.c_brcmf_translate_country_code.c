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
struct brcmfmac_pd_cc_entry {char* iso3166; int /*<<< orphan*/  cc; int /*<<< orphan*/  rev; } ;
struct brcmfmac_pd_cc {int table_size; struct brcmfmac_pd_cc_entry* table; } ;
struct brcmf_pub {TYPE_1__* settings; } ;
struct brcmf_fil_country_le {char* country_abbrev; int /*<<< orphan*/  ccode; int /*<<< orphan*/  rev; } ;
typedef  int s32 ;
struct TYPE_2__ {struct brcmfmac_pd_cc* country_codes; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_COUNTRY_BUF_SZ ; 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct brcmf_fil_country_le*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 brcmf_translate_country_code(struct brcmf_pub *drvr, char alpha2[2],
					struct brcmf_fil_country_le *ccreq)
{
	struct brcmfmac_pd_cc *country_codes;
	struct brcmfmac_pd_cc_entry *cc;
	s32 found_index;
	int i;

	country_codes = drvr->settings->country_codes;
	if (!country_codes) {
		brcmf_dbg(TRACE, "No country codes configured for device\n");
		return -EINVAL;
	}

	if ((alpha2[0] == ccreq->country_abbrev[0]) &&
	    (alpha2[1] == ccreq->country_abbrev[1])) {
		brcmf_dbg(TRACE, "Country code already set\n");
		return -EAGAIN;
	}

	found_index = -1;
	for (i = 0; i < country_codes->table_size; i++) {
		cc = &country_codes->table[i];
		if ((cc->iso3166[0] == '\0') && (found_index == -1))
			found_index = i;
		if ((cc->iso3166[0] == alpha2[0]) &&
		    (cc->iso3166[1] == alpha2[1])) {
			found_index = i;
			break;
		}
	}
	if (found_index == -1) {
		brcmf_dbg(TRACE, "No country code match found\n");
		return -EINVAL;
	}
	memset(ccreq, 0, sizeof(*ccreq));
	ccreq->rev = cpu_to_le32(country_codes->table[found_index].rev);
	memcpy(ccreq->ccode, country_codes->table[found_index].cc,
	       BRCMF_COUNTRY_BUF_SZ);
	ccreq->country_abbrev[0] = alpha2[0];
	ccreq->country_abbrev[1] = alpha2[1];
	ccreq->country_abbrev[2] = 0;

	return 0;
}