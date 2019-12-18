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
typedef  size_t uint ;
typedef  int u8 ;
struct brcms_c_rateset {size_t count; int* rates; } ;
struct brcms_c_info {TYPE_1__* stf; } ;
struct TYPE_2__ {int /*<<< orphan*/  txstreams; } ;

/* Variables and functions */
 int BRCMS_RATE_MASK ; 
 int brcms_basic_rate (struct brcms_c_info*,int) ; 
 int /*<<< orphan*/  brcms_c_rateset_copy (struct brcms_c_rateset const*,struct brcms_c_rateset*) ; 
 struct brcms_c_rateset* brcms_c_rateset_get_hwrs (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_rateset_mcs_upd (struct brcms_c_rateset*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_write_rate_shm (struct brcms_c_info*,int,int) ; 

__attribute__((used)) static void brcms_c_set_ratetable(struct brcms_c_info *wlc)
{
	const struct brcms_c_rateset *rs_dflt;
	struct brcms_c_rateset rs;
	u8 rate, basic_rate;
	uint i;

	rs_dflt = brcms_c_rateset_get_hwrs(wlc);

	brcms_c_rateset_copy(rs_dflt, &rs);
	brcms_c_rateset_mcs_upd(&rs, wlc->stf->txstreams);

	/* walk the phy rate table and update SHM basic rate lookup table */
	for (i = 0; i < rs.count; i++) {
		rate = rs.rates[i] & BRCMS_RATE_MASK;

		/* for a given rate brcms_basic_rate returns the rate at
		 * which a response ACK/CTS should be sent.
		 */
		basic_rate = brcms_basic_rate(wlc, rate);
		if (basic_rate == 0)
			/* This should only happen if we are using a
			 * restricted rateset.
			 */
			basic_rate = rs.rates[0] & BRCMS_RATE_MASK;

		brcms_c_write_rate_shm(wlc, rate, basic_rate);
	}
}