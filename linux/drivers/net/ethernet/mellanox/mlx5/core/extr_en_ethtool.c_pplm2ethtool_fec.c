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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ETHTOOL_FEC_AUTO ; 
 int find_first_bit (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pplm_fec_2_ethtool ; 

__attribute__((used)) static u32 pplm2ethtool_fec(u_long fec_mode, unsigned long size)
{
	int mode = 0;

	if (!fec_mode)
		return ETHTOOL_FEC_AUTO;

	mode = find_first_bit(&fec_mode, size);

	if (mode < ARRAY_SIZE(pplm_fec_2_ethtool))
		return pplm_fec_2_ethtool[mode];

	return 0;
}