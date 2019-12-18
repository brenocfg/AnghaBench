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
struct tb {int dummy; } ;
struct icm_tr_pkg_driver_ready_response {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  code; } ;
struct icm_pkg_driver_ready {TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  request ;
typedef  int /*<<< orphan*/  reply ;
typedef  enum tb_security_level { ____Placeholder_tb_security_level } tb_security_level ;

/* Variables and functions */
 int /*<<< orphan*/  ICM_DRIVER_READY ; 
 int icm_request (struct tb*,struct icm_pkg_driver_ready*,int,struct icm_tr_pkg_driver_ready_response*,int,int,int) ; 
 int /*<<< orphan*/  memset (struct icm_tr_pkg_driver_ready_response*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
icm_icl_driver_ready(struct tb *tb, enum tb_security_level *security_level,
		    size_t *nboot_acl, bool *rpm)
{
	struct icm_tr_pkg_driver_ready_response reply;
	struct icm_pkg_driver_ready request = {
		.hdr.code = ICM_DRIVER_READY,
	};
	int ret;

	memset(&reply, 0, sizeof(reply));
	ret = icm_request(tb, &request, sizeof(request), &reply, sizeof(reply),
			  1, 20000);
	if (ret)
		return ret;

	/* Ice Lake always supports RTD3 */
	if (rpm)
		*rpm = true;

	return 0;
}