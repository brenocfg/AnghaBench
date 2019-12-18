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
struct tb_xdomain {int dummy; } ;
struct tb {int dummy; } ;

/* Variables and functions */
 int icm_tr_xdomain_tear_down (struct tb*,struct tb_xdomain*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int icm_tr_disconnect_xdomain_paths(struct tb *tb, struct tb_xdomain *xd)
{
	int ret;

	ret = icm_tr_xdomain_tear_down(tb, xd, 1);
	if (ret)
		return ret;

	usleep_range(10, 50);
	return icm_tr_xdomain_tear_down(tb, xd, 2);
}