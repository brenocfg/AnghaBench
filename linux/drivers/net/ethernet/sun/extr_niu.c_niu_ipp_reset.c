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
struct niu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPP_CFIG ; 
 int /*<<< orphan*/  IPP_CFIG_SOFT_RST ; 
 int niu_set_and_wait_clear_ipp (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*) ; 

__attribute__((used)) static int niu_ipp_reset(struct niu *np)
{
	return niu_set_and_wait_clear_ipp(np, IPP_CFIG, IPP_CFIG_SOFT_RST,
					  1000, 100, "IPP_CFIG");
}