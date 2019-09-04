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
struct TYPE_2__ {int /*<<< orphan*/  (* progress ) (char*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  H_IS_LONG_BUSY (long) ; 
 long enable_little_endian_exceptions () ; 
 int /*<<< orphan*/  get_longbusy_msecs (long) ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 TYPE_1__ ppc_md ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ ) ; 

void pseries_little_endian_exceptions(void)
{
	long rc;

	while (1) {
		rc = enable_little_endian_exceptions();
		if (!H_IS_LONG_BUSY(rc))
			break;
		mdelay(get_longbusy_msecs(rc));
	}
	if (rc) {
		ppc_md.progress("H_SET_MODE LE exception fail", 0);
		panic("Could not enable little endian exceptions");
	}
}