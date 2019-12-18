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
typedef  int u32 ;
typedef  int /*<<< orphan*/  our_ver ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int FCOPY_CURRENT_VERSION ; 
#define  FCOPY_VERSION_0 129 
#define  FCOPY_VERSION_1 128 
 int dm_reg_value ; 
 int /*<<< orphan*/  fcopy_register_done ; 
 int /*<<< orphan*/  hvt ; 
 int /*<<< orphan*/  hvutil_transport_send (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static int fcopy_handle_handshake(u32 version)
{
	u32 our_ver = FCOPY_CURRENT_VERSION;

	switch (version) {
	case FCOPY_VERSION_0:
		/* Daemon doesn't expect us to reply */
		dm_reg_value = version;
		break;
	case FCOPY_VERSION_1:
		/* Daemon expects us to reply with our own version */
		if (hvutil_transport_send(hvt, &our_ver, sizeof(our_ver),
		    fcopy_register_done))
			return -EFAULT;
		dm_reg_value = version;
		break;
	default:
		/*
		 * For now we will fail the registration.
		 * If and when we have multiple versions to
		 * deal with, we will be backward compatible.
		 * We will add this code when needed.
		 */
		return -EINVAL;
	}
	pr_debug("FCP: userspace daemon ver. %d connected\n", version);
	return 0;
}