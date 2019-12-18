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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;
struct adapter {int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  cxgb4_free_mac_filt (struct adapter*,unsigned int,unsigned int,int /*<<< orphan*/  const**,int) ; 
 scalar_t__ cxgb4_mps_ref_inc (struct adapter*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int t4_alloc_mac_filt (struct adapter*,int /*<<< orphan*/ ,unsigned int,int,unsigned int,int /*<<< orphan*/  const**,int*,int /*<<< orphan*/ *,int) ; 

int cxgb4_alloc_mac_filt(struct adapter *adap, unsigned int viid,
			 bool free, unsigned int naddr, const u8 **addr,
			 u16 *idx, u64 *hash, bool sleep_ok)
{
	int ret, i;

	ret = t4_alloc_mac_filt(adap, adap->mbox, viid, free,
				naddr, addr, idx, hash, sleep_ok);
	if (ret < 0)
		return ret;

	for (i = 0; i < naddr; i++) {
		if (idx[i] != 0xffff) {
			if (cxgb4_mps_ref_inc(adap, addr[i], idx[i], NULL)) {
				ret = -ENOMEM;
				goto error;
			}
		}
	}

	goto out;
error:
	cxgb4_free_mac_filt(adap, viid, naddr, addr, sleep_ok);

out:
	/* Returns a negative error number or the number of filters allocated */
	return ret;
}