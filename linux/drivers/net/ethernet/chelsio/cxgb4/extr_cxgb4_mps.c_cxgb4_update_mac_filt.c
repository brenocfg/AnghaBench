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
struct port_info {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int cxgb4_change_mac (struct port_info*,unsigned int,int*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cxgb4_mps_ref_inc (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 

int cxgb4_update_mac_filt(struct port_info *pi, unsigned int viid,
			  int *tcam_idx, const u8 *addr,
			  bool persistent, u8 *smt_idx)
{
	int ret;

	ret = cxgb4_change_mac(pi, viid, tcam_idx,
			       addr, persistent, smt_idx);
	if (ret < 0)
		return ret;

	cxgb4_mps_ref_inc(pi->adapter, addr, *tcam_idx, NULL);
	return ret;
}