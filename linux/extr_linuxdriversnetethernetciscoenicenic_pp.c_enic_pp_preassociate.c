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
struct enic_port_profile {int dummy; } ;
struct enic {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static int enic_pp_preassociate(struct enic *enic, int vf,
	struct enic_port_profile *prev_pp, int *restore_pp)
{
	return -EOPNOTSUPP;
}