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
struct tb_nhi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  icl_nhi_force_power (struct tb_nhi*,int) ; 

__attribute__((used)) static void icl_nhi_shutdown(struct tb_nhi *nhi)
{
	icl_nhi_force_power(nhi, false);
}