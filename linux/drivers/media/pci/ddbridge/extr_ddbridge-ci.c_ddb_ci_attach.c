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
typedef  int /*<<< orphan*/  u32 ;
struct ddb_port {int type; int /*<<< orphan*/  en; TYPE_1__* dvb; } ;
struct TYPE_2__ {int /*<<< orphan*/  adap; } ;

/* Variables and functions */
#define  DDB_CI_EXTERNAL_SONY 131 
#define  DDB_CI_EXTERNAL_XO2 130 
#define  DDB_CI_EXTERNAL_XO2_B 129 
#define  DDB_CI_INTERNAL 128 
 int ENODEV ; 
 int /*<<< orphan*/  ci_attach (struct ddb_port*) ; 
 int ci_cxd2099_attach (struct ddb_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ci_xo2_attach (struct ddb_port*) ; 
 int /*<<< orphan*/  dvb_ca_en50221_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int ddb_ci_attach(struct ddb_port *port, u32 bitrate)
{
	int ret;

	switch (port->type) {
	case DDB_CI_EXTERNAL_SONY:
		ret = ci_cxd2099_attach(port, bitrate);
		if (ret)
			return -ENODEV;
		break;
	case DDB_CI_EXTERNAL_XO2:
	case DDB_CI_EXTERNAL_XO2_B:
		ci_xo2_attach(port);
		break;
	case DDB_CI_INTERNAL:
		ci_attach(port);
		break;
	default:
		return -ENODEV;
	}

	if (!port->en)
		return -ENODEV;
	dvb_ca_en50221_init(port->dvb[0].adap, port->en, 0, 1);
	return 0;
}