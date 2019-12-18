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
struct brcmf_pub {TYPE_1__* proto; } ;
struct brcmf_fws_info {int dummy; } ;
struct brcmf_bcdc {struct brcmf_fws_info* fws; } ;
struct TYPE_2__ {struct brcmf_bcdc* pd; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct brcmf_fws_info*) ; 
 int PTR_ERR (struct brcmf_fws_info*) ; 
 struct brcmf_fws_info* brcmf_fws_attach (struct brcmf_pub*) ; 

__attribute__((used)) static int
brcmf_proto_bcdc_init_done(struct brcmf_pub *drvr)
{
	struct brcmf_bcdc *bcdc = drvr->proto->pd;
	struct brcmf_fws_info *fws;

	fws = brcmf_fws_attach(drvr);
	if (IS_ERR(fws))
		return PTR_ERR(fws);

	bcdc->fws = fws;
	return 0;
}