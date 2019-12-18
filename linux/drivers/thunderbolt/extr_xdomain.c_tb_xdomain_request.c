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
 int __tb_xdomain_request (int /*<<< orphan*/ ,void const*,size_t,int,void*,size_t,int,unsigned int) ; 

int tb_xdomain_request(struct tb_xdomain *xd, const void *request,
	size_t request_size, enum tb_cfg_pkg_type request_type,
	void *response, size_t response_size,
	enum tb_cfg_pkg_type response_type, unsigned int timeout_msec)
{
	return __tb_xdomain_request(xd->tb->ctl, request, request_size,
				    request_type, response, response_size,
				    response_type, timeout_msec);
}