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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct ib_qp_security {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; } ;
struct ib_ports_pkeys {TYPE_1__ alt; TYPE_1__ main; } ;

/* Variables and functions */
 scalar_t__ IB_PORT_PKEY_NOT_VALID ; 
 int enforce_qp_pkey_security (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_qp_security*) ; 
 int get_pkey_and_subnet_prefix (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_qp_port_pkey_settings(struct ib_ports_pkeys *pps,
				       struct ib_qp_security *sec)
{
	u64 subnet_prefix;
	u16 pkey;
	int ret = 0;

	if (!pps)
		return 0;

	if (pps->main.state != IB_PORT_PKEY_NOT_VALID) {
		ret = get_pkey_and_subnet_prefix(&pps->main,
						 &pkey,
						 &subnet_prefix);
		if (ret)
			return ret;

		ret = enforce_qp_pkey_security(pkey,
					       subnet_prefix,
					       sec);
		if (ret)
			return ret;
	}

	if (pps->alt.state != IB_PORT_PKEY_NOT_VALID) {
		ret = get_pkey_and_subnet_prefix(&pps->alt,
						 &pkey,
						 &subnet_prefix);
		if (ret)
			return ret;

		ret = enforce_qp_pkey_security(pkey,
					       subnet_prefix,
					       sec);
	}

	return ret;
}