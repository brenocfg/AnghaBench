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
struct TYPE_2__ {char* nodename; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PCI_VENDOR_ID_INTEL ; 
 int rebuild_property_block () ; 
 int /*<<< orphan*/  tb_property_add_immediate (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  tb_property_add_text (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * tb_property_create_dir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tb_property_free_dir (int /*<<< orphan*/ *) ; 
 TYPE_1__* utsname () ; 
 int /*<<< orphan*/ * xdomain_property_dir ; 

int tb_xdomain_init(void)
{
	int ret;

	xdomain_property_dir = tb_property_create_dir(NULL);
	if (!xdomain_property_dir)
		return -ENOMEM;

	/*
	 * Initialize standard set of properties without any service
	 * directories. Those will be added by service drivers
	 * themselves when they are loaded.
	 */
	tb_property_add_immediate(xdomain_property_dir, "vendorid",
				  PCI_VENDOR_ID_INTEL);
	tb_property_add_text(xdomain_property_dir, "vendorid", "Intel Corp.");
	tb_property_add_immediate(xdomain_property_dir, "deviceid", 0x1);
	tb_property_add_text(xdomain_property_dir, "deviceid",
			     utsname()->nodename);
	tb_property_add_immediate(xdomain_property_dir, "devicerv", 0x80000100);

	ret = rebuild_property_block();
	if (ret) {
		tb_property_free_dir(xdomain_property_dir);
		xdomain_property_dir = NULL;
	}

	return ret;
}