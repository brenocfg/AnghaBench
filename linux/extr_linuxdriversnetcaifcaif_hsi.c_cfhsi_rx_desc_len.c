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
typedef  scalar_t__ u16 ;
struct cfhsi_desc {int header; scalar_t__ offset; scalar_t__* cffrm_len; } ;

/* Variables and functions */
 scalar_t__ CFHSI_MAX_EMB_FRM_SZ ; 
 int CFHSI_MAX_PKTS ; 
 int CFHSI_PIGGY_DESC ; 
 int EPROTO ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 

__attribute__((used)) static int cfhsi_rx_desc_len(struct cfhsi_desc *desc)
{
	int xfer_sz = 0;
	int nfrms = 0;
	u16 *plen;

	if ((desc->header & ~CFHSI_PIGGY_DESC) ||
			(desc->offset > CFHSI_MAX_EMB_FRM_SZ)) {

		pr_err("Invalid descriptor. %x %x\n", desc->header,
				desc->offset);
		return -EPROTO;
	}

	/* Calculate transfer length. */
	plen = desc->cffrm_len;
	while (nfrms < CFHSI_MAX_PKTS && *plen) {
		xfer_sz += *plen;
		plen++;
		nfrms++;
	}

	if (xfer_sz % 4) {
		pr_err("Invalid payload len: %d, ignored.\n", xfer_sz);
		return -EPROTO;
	}
	return xfer_sz;
}