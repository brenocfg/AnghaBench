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
struct TYPE_2__ {int cim_la_size; int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 unsigned int UPDBGLAEN_F ; 
 unsigned int UPDBGLARDEN_F ; 
 unsigned int UPDBGLARDPTR_M ; 
 unsigned int UPDBGLARDPTR_V (unsigned int) ; 
 unsigned int UPDBGLAWRPTR_G (unsigned int) ; 
 int /*<<< orphan*/  UP_UP_DBG_LA_CFG_A ; 
 int /*<<< orphan*/  UP_UP_DBG_LA_DATA_A ; 
 scalar_t__ is_t6 (int /*<<< orphan*/ ) ; 
 int t4_cim_read (struct adapter*,int /*<<< orphan*/ ,int,unsigned int*) ; 
 int t4_cim_write1 (struct adapter*,int /*<<< orphan*/ ,unsigned int) ; 

int t4_cim_read_la(struct adapter *adap, u32 *la_buf, unsigned int *wrptr)
{
	int i, ret;
	unsigned int cfg, val, idx;

	ret = t4_cim_read(adap, UP_UP_DBG_LA_CFG_A, 1, &cfg);
	if (ret)
		return ret;

	if (cfg & UPDBGLAEN_F) {	/* LA is running, freeze it */
		ret = t4_cim_write1(adap, UP_UP_DBG_LA_CFG_A, 0);
		if (ret)
			return ret;
	}

	ret = t4_cim_read(adap, UP_UP_DBG_LA_CFG_A, 1, &val);
	if (ret)
		goto restart;

	idx = UPDBGLAWRPTR_G(val);
	if (wrptr)
		*wrptr = idx;

	for (i = 0; i < adap->params.cim_la_size; i++) {
		ret = t4_cim_write1(adap, UP_UP_DBG_LA_CFG_A,
				    UPDBGLARDPTR_V(idx) | UPDBGLARDEN_F);
		if (ret)
			break;
		ret = t4_cim_read(adap, UP_UP_DBG_LA_CFG_A, 1, &val);
		if (ret)
			break;
		if (val & UPDBGLARDEN_F) {
			ret = -ETIMEDOUT;
			break;
		}
		ret = t4_cim_read(adap, UP_UP_DBG_LA_DATA_A, 1, &la_buf[i]);
		if (ret)
			break;

		/* Bits 0-3 of UpDbgLaRdPtr can be between 0000 to 1001 to
		 * identify the 32-bit portion of the full 312-bit data
		 */
		if (is_t6(adap->params.chip) && (idx & 0xf) >= 9)
			idx = (idx & 0xff0) + 0x10;
		else
			idx++;
		/* address can't exceed 0xfff */
		idx &= UPDBGLARDPTR_M;
	}
restart:
	if (cfg & UPDBGLAEN_F) {
		int r = t4_cim_write1(adap, UP_UP_DBG_LA_CFG_A,
				      cfg & ~UPDBGLARDEN_F);
		if (!ret)
			ret = r;
	}
	return ret;
}