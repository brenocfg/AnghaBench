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
typedef  int u64 ;
struct niu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FFLP_CFG_1 ; 
 int FFLP_CFG_1_CAMLAT ; 
 int FFLP_CFG_1_CAMLAT_SHIFT ; 
 int FFLP_CFG_1_CAMRATIO ; 
 int FFLP_CFG_1_CAMRATIO_SHIFT ; 
 int FFLP_CFG_1_FFLPINITDONE ; 
 int nr64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tcam_set_lat_and_ratio(struct niu *np, u64 latency, u64 ratio)
{
	u64 val = nr64(FFLP_CFG_1);

	val &= ~(FFLP_CFG_1_FFLPINITDONE |
		 FFLP_CFG_1_CAMLAT |
		 FFLP_CFG_1_CAMRATIO);
	val |= (latency << FFLP_CFG_1_CAMLAT_SHIFT);
	val |= (ratio << FFLP_CFG_1_CAMRATIO_SHIFT);
	nw64(FFLP_CFG_1, val);

	val = nr64(FFLP_CFG_1);
	val |= FFLP_CFG_1_FFLPINITDONE;
	nw64(FFLP_CFG_1, val);
}