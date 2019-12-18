#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct brcmf_pub {int /*<<< orphan*/  feat_flags; } ;
struct brcmf_if {struct brcmf_pub* drvr; } ;
typedef  enum brcmf_feat_id { ____Placeholder_brcmf_feat_id } brcmf_feat_id ;
typedef  int /*<<< orphan*/  caps ;
struct TYPE_3__ {int feature; int /*<<< orphan*/  fwcap_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  INFO ; 
 int MAX_CAPS_BUFFER_SIZE ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,int) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 char** brcmf_feat_names ; 
 int brcmf_fil_iovar_data_get (struct brcmf_if*,char*,char*,int) ; 
 TYPE_1__* brcmf_fwcap_map ; 
 scalar_t__ strnstr (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void brcmf_feat_firmware_capabilities(struct brcmf_if *ifp)
{
	struct brcmf_pub *drvr = ifp->drvr;
	char caps[MAX_CAPS_BUFFER_SIZE];
	enum brcmf_feat_id id;
	int i, err;

	err = brcmf_fil_iovar_data_get(ifp, "cap", caps, sizeof(caps));
	if (err) {
		bphy_err(drvr, "could not get firmware cap (%d)\n", err);
		return;
	}

	brcmf_dbg(INFO, "[ %s]\n", caps);

	for (i = 0; i < ARRAY_SIZE(brcmf_fwcap_map); i++) {
		if (strnstr(caps, brcmf_fwcap_map[i].fwcap_id, sizeof(caps))) {
			id = brcmf_fwcap_map[i].feature;
			brcmf_dbg(INFO, "enabling feature: %s\n",
				  brcmf_feat_names[id]);
			ifp->drvr->feat_flags |= BIT(id);
		}
	}
}