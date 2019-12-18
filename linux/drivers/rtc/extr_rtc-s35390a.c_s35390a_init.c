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
typedef  int u8 ;
struct s35390a {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  S35390A_CMD_STATUS1 ; 
 int S35390A_FLAG_24H ; 
 int S35390A_FLAG_BLD ; 
 int S35390A_FLAG_POC ; 
 int S35390A_FLAG_RESET ; 
 int s35390a_get_reg (struct s35390a*,int /*<<< orphan*/ ,int*,int) ; 
 int s35390a_set_reg (struct s35390a*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int s35390a_init(struct s35390a *s35390a)
{
	u8 buf;
	int ret;
	unsigned initcount = 0;

	/*
	 * At least one of POC and BLD are set, so reinitialise chip. Keeping
	 * this information in the hardware to know later that the time isn't
	 * valid is unfortunately not possible because POC and BLD are cleared
	 * on read. So the reset is best done now.
	 *
	 * The 24H bit is kept over reset, so set it already here.
	 */
initialize:
	buf = S35390A_FLAG_RESET | S35390A_FLAG_24H;
	ret = s35390a_set_reg(s35390a, S35390A_CMD_STATUS1, &buf, 1);

	if (ret < 0)
		return ret;

	ret = s35390a_get_reg(s35390a, S35390A_CMD_STATUS1, &buf, 1);
	if (ret < 0)
		return ret;

	if (buf & (S35390A_FLAG_POC | S35390A_FLAG_BLD)) {
		/* Try up to five times to reset the chip */
		if (initcount < 5) {
			++initcount;
			goto initialize;
		} else
			return -EIO;
	}

	return 1;
}