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
typedef  int /*<<< orphan*/  u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int CHELSIO_CHIP_CODE (int const,int /*<<< orphan*/ ) ; 
#define  CHELSIO_T4 130 
#define  CHELSIO_T5 129 
#define  CHELSIO_T6 128 
 int EINVAL ; 
 int /*<<< orphan*/  PL_REV_A ; 
 int /*<<< orphan*/  REV_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int t4_get_chip_type(struct adapter *adap, int ver)
{
	u32 pl_rev = REV_G(t4_read_reg(adap, PL_REV_A));

	switch (ver) {
	case CHELSIO_T4:
		return CHELSIO_CHIP_CODE(CHELSIO_T4, pl_rev);
	case CHELSIO_T5:
		return CHELSIO_CHIP_CODE(CHELSIO_T5, pl_rev);
	case CHELSIO_T6:
		return CHELSIO_CHIP_CODE(CHELSIO_T6, pl_rev);
	default:
		break;
	}
	return -EINVAL;
}