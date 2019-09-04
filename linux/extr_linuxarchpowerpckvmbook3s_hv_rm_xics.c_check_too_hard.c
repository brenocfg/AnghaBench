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
struct kvmppc_xics {scalar_t__ real_mode_dbg; } ;
struct kvmppc_icp {scalar_t__ rm_action; } ;

/* Variables and functions */
 int H_SUCCESS ; 
 int H_TOO_HARD ; 

__attribute__((used)) static inline int check_too_hard(struct kvmppc_xics *xics,
				 struct kvmppc_icp *icp)
{
	return (xics->real_mode_dbg || icp->rm_action) ? H_TOO_HARD : H_SUCCESS;
}