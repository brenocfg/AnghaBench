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
struct qib_devdata {int dummy; } ;

/* Variables and functions */
 int R_RDY ; 
 int R_TDO_LSB ; 
 int /*<<< orphan*/  kr_r_access ; 
 int qib_read_kreg32 (struct qib_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qib_r_wait_for_rdy(struct qib_devdata *dd)
{
	u64 val;
	int timeout;

	for (timeout = 0; timeout < 100 ; ++timeout) {
		val = qib_read_kreg32(dd, kr_r_access);
		if (val & R_RDY)
			return (val >> R_TDO_LSB) & 1;
	}
	return -1;
}