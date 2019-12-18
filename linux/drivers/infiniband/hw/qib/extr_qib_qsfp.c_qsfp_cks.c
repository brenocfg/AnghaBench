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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct qib_pportdata {int dummy; } ;

/* Variables and functions */
 int qsfp_read (struct qib_pportdata*,int,scalar_t__*,int) ; 

__attribute__((used)) static int qsfp_cks(struct qib_pportdata *ppd, int first, int next)
{
	int ret;
	u16 cks;
	u8 bval;

	cks = 0;
	while (first < next) {
		ret = qsfp_read(ppd, first, &bval, 1);
		if (ret < 0)
			goto bail;
		cks += bval;
		++first;
	}
	ret = cks & 0xFF;
bail:
	return ret;

}