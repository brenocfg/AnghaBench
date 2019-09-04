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
struct intel_gvt {int dummy; } ;

/* Variables and functions */
 int in_whitelist (unsigned int) ; 

bool intel_gvt_in_force_nonpriv_whitelist(struct intel_gvt *gvt,
					  unsigned int offset)
{
	return in_whitelist(offset);
}