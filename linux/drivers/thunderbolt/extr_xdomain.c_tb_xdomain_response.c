#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tb_xdomain {TYPE_1__* tb; } ;
typedef  enum tb_cfg_pkg_type { ____Placeholder_tb_cfg_pkg_type } tb_cfg_pkg_type ;
struct TYPE_2__ {int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int __tb_xdomain_response (int /*<<< orphan*/ ,void const*,size_t,int) ; 

int tb_xdomain_response(struct tb_xdomain *xd, const void *response,
			size_t size, enum tb_cfg_pkg_type type)
{
	return __tb_xdomain_response(xd->tb->ctl, response, size, type);
}