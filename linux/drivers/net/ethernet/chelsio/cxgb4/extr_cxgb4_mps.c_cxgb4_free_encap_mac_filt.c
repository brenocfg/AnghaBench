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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxgb4_mps_ref_dec (struct adapter*,int) ; 
 int t4_free_encap_mac_filt (struct adapter*,unsigned int,int,int) ; 

int cxgb4_free_encap_mac_filt(struct adapter *adap, unsigned int viid,
			      int idx, bool sleep_ok)
{
	int ret = 0;

	if (!cxgb4_mps_ref_dec(adap, idx))
		ret = t4_free_encap_mac_filt(adap, viid, idx, sleep_ok);

	return ret;
}