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
typedef  int /*<<< orphan*/  u8 ;
struct adapter {int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxgb4_mps_ref_dec_by_mac (struct adapter*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int t4_free_mac_filt (struct adapter*,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/  const**,int) ; 

int cxgb4_free_mac_filt(struct adapter *adap, unsigned int viid,
			unsigned int naddr, const u8 **addr, bool sleep_ok)
{
	int ret, i;

	for (i = 0; i < naddr; i++) {
		if (!cxgb4_mps_ref_dec_by_mac(adap, addr[i], NULL)) {
			ret = t4_free_mac_filt(adap, adap->mbox, viid,
					       1, &addr[i], sleep_ok);
			if (ret < 0)
				return ret;
		}
	}

	/* return number of filters freed */
	return naddr;
}