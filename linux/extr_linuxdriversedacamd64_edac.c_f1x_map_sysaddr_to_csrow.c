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
typedef  int /*<<< orphan*/  u64 ;
struct mem_ctl_info {struct amd64_pvt* pvt_info; } ;
struct err_info {int /*<<< orphan*/  syndrome; int /*<<< orphan*/  channel; int /*<<< orphan*/  err_code; int /*<<< orphan*/  csrow; } ;
struct amd64_pvt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_CSROW ; 
 scalar_t__ dct_ganging_enabled (struct amd64_pvt*) ; 
 int /*<<< orphan*/  error_address_to_page_and_offset (int /*<<< orphan*/ ,struct err_info*) ; 
 int /*<<< orphan*/  f1x_translate_sysaddr_to_cs (struct amd64_pvt*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_channel_from_ecc_syndrome (struct mem_ctl_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void f1x_map_sysaddr_to_csrow(struct mem_ctl_info *mci, u64 sys_addr,
				     struct err_info *err)
{
	struct amd64_pvt *pvt = mci->pvt_info;

	error_address_to_page_and_offset(sys_addr, err);

	err->csrow = f1x_translate_sysaddr_to_cs(pvt, sys_addr, &err->channel);
	if (err->csrow < 0) {
		err->err_code = ERR_CSROW;
		return;
	}

	/*
	 * We need the syndromes for channel detection only when we're
	 * ganged. Otherwise @chan should already contain the channel at
	 * this point.
	 */
	if (dct_ganging_enabled(pvt))
		err->channel = get_channel_from_ecc_syndrome(mci, err->syndrome);
}