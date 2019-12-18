#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct brcmf_pub {int /*<<< orphan*/  bus_if; TYPE_1__* proto; } ;
struct brcmf_proto_bcdc_dcmd {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct brcmf_bcdc {TYPE_2__ msg; } ;
struct TYPE_3__ {scalar_t__ pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCDC ; 
 int BCDC_DCMD_ID (int /*<<< orphan*/ ) ; 
 int brcmf_bus_rxctl (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmf_proto_bcdc_cmplt(struct brcmf_pub *drvr, u32 id, u32 len)
{
	int ret;
	struct brcmf_bcdc *bcdc = (struct brcmf_bcdc *)drvr->proto->pd;

	brcmf_dbg(BCDC, "Enter\n");
	len += sizeof(struct brcmf_proto_bcdc_dcmd);
	do {
		ret = brcmf_bus_rxctl(drvr->bus_if, (unsigned char *)&bcdc->msg,
				      len);
		if (ret < 0)
			break;
	} while (BCDC_DCMD_ID(le32_to_cpu(bcdc->msg.flags)) != id);

	return ret;
}