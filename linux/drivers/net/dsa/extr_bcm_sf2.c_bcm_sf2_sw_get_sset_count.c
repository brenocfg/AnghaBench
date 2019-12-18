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
struct dsa_switch {int dummy; } ;

/* Variables and functions */
 int b53_get_sset_count (struct dsa_switch*,int,int) ; 
 scalar_t__ bcm_sf2_cfp_get_sset_count (struct dsa_switch*,int,int) ; 

__attribute__((used)) static int bcm_sf2_sw_get_sset_count(struct dsa_switch *ds, int port,
				     int sset)
{
	int cnt = b53_get_sset_count(ds, port, sset);

	if (cnt < 0)
		return cnt;

	cnt += bcm_sf2_cfp_get_sset_count(ds, port, sset);

	return cnt;
}