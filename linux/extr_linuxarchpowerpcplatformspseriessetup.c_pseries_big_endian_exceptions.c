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

/* Variables and functions */
 int /*<<< orphan*/  H_IS_LONG_BUSY (long) ; 
 long enable_big_endian_exceptions () ; 
 int /*<<< orphan*/  get_longbusy_msecs (long) ; 
 int /*<<< orphan*/  kdump_in_progress () ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

void pseries_big_endian_exceptions(void)
{
	long rc;

	while (1) {
		rc = enable_big_endian_exceptions();
		if (!H_IS_LONG_BUSY(rc))
			break;
		mdelay(get_longbusy_msecs(rc));
	}

	/*
	 * At this point it is unlikely panic() will get anything
	 * out to the user, since this is called very late in kexec
	 * but at least this will stop us from continuing on further
	 * and creating an even more difficult to debug situation.
	 *
	 * There is a known problem when kdump'ing, if cpus are offline
	 * the above call will fail. Rather than panicking again, keep
	 * going and hope the kdump kernel is also little endian, which
	 * it usually is.
	 */
	if (rc && !kdump_in_progress())
		panic("Could not enable big endian exceptions");
}