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
typedef  int /*<<< orphan*/  uint ;
typedef  int u32 ;
struct brcmf_pub {TYPE_1__* proto; } ;
struct brcmf_proto_bcdc_dcmd {int /*<<< orphan*/  status; int /*<<< orphan*/  flags; } ;
struct brcmf_bcdc {int reqid; struct brcmf_proto_bcdc_dcmd msg; } ;
struct TYPE_2__ {scalar_t__ pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCDC ; 
 int BCDC_DCMD_ERROR ; 
 int BCDC_DCMD_ID_MASK ; 
 int BCDC_DCMD_ID_SHIFT ; 
 int EINVAL ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_get_ifp (struct brcmf_pub*,int) ; 
 int /*<<< orphan*/  brcmf_ifname (int /*<<< orphan*/ ) ; 
 int brcmf_proto_bcdc_cmplt (struct brcmf_pub*,int,int /*<<< orphan*/ ) ; 
 int brcmf_proto_bcdc_msg (struct brcmf_pub*,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
brcmf_proto_bcdc_set_dcmd(struct brcmf_pub *drvr, int ifidx, uint cmd,
			  void *buf, uint len, int *fwerr)
{
	struct brcmf_bcdc *bcdc = (struct brcmf_bcdc *)drvr->proto->pd;
	struct brcmf_proto_bcdc_dcmd *msg = &bcdc->msg;
	int ret;
	u32 flags, id;

	brcmf_dbg(BCDC, "Enter, cmd %d len %d\n", cmd, len);

	*fwerr = 0;
	ret = brcmf_proto_bcdc_msg(drvr, ifidx, cmd, buf, len, true);
	if (ret < 0)
		goto done;

	ret = brcmf_proto_bcdc_cmplt(drvr, bcdc->reqid, len);
	if (ret < 0)
		goto done;

	flags = le32_to_cpu(msg->flags);
	id = (flags & BCDC_DCMD_ID_MASK) >> BCDC_DCMD_ID_SHIFT;

	if (id != bcdc->reqid) {
		bphy_err(drvr, "%s: unexpected request id %d (expected %d)\n",
			 brcmf_ifname(brcmf_get_ifp(drvr, ifidx)), id,
			 bcdc->reqid);
		ret = -EINVAL;
		goto done;
	}

	ret = 0;

	/* Check the ERROR flag */
	if (flags & BCDC_DCMD_ERROR)
		*fwerr = le32_to_cpu(msg->status);

done:
	return ret;
}