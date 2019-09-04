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
struct cyttsp4 {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int cyttsp4_hw_hard_reset (struct cyttsp4*) ; 
 int cyttsp4_hw_soft_reset (struct cyttsp4*) ; 

__attribute__((used)) static int cyttsp4_hw_reset(struct cyttsp4 *cd)
{
	int rc = cyttsp4_hw_hard_reset(cd);
	if (rc == -ENOSYS)
		rc = cyttsp4_hw_soft_reset(cd);
	return rc;
}