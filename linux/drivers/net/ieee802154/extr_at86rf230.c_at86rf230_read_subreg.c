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
struct at86rf230_local {int dummy; } ;

/* Variables and functions */
 int __at86rf230_read (struct at86rf230_local*,unsigned int,unsigned int*) ; 

__attribute__((used)) static inline int
at86rf230_read_subreg(struct at86rf230_local *lp,
		      unsigned int addr, unsigned int mask,
		      unsigned int shift, unsigned int *data)
{
	int rc;

	rc = __at86rf230_read(lp, addr, data);
	if (!rc)
		*data = (*data & mask) >> shift;

	return rc;
}