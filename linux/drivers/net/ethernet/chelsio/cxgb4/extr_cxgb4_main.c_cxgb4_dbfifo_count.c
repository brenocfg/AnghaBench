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
typedef  unsigned int u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 unsigned int HP_COUNT_G (unsigned int) ; 
 unsigned int HP_COUNT_T5_G (unsigned int) ; 
 unsigned int LP_COUNT_G (unsigned int) ; 
 unsigned int LP_COUNT_T5_G (unsigned int) ; 
 int /*<<< orphan*/  SGE_DBFIFO_STATUS2_A ; 
 int /*<<< orphan*/  SGE_DBFIFO_STATUS_A ; 
 scalar_t__ is_t4 (int /*<<< orphan*/ ) ; 
 struct adapter* netdev2adap (struct net_device const*) ; 
 unsigned int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

unsigned int cxgb4_dbfifo_count(const struct net_device *dev, int lpfifo)
{
	struct adapter *adap = netdev2adap(dev);
	u32 v1, v2, lp_count, hp_count;

	v1 = t4_read_reg(adap, SGE_DBFIFO_STATUS_A);
	v2 = t4_read_reg(adap, SGE_DBFIFO_STATUS2_A);
	if (is_t4(adap->params.chip)) {
		lp_count = LP_COUNT_G(v1);
		hp_count = HP_COUNT_G(v1);
	} else {
		lp_count = LP_COUNT_T5_G(v1);
		hp_count = HP_COUNT_T5_G(v2);
	}
	return lpfifo ? lp_count : hp_count;
}