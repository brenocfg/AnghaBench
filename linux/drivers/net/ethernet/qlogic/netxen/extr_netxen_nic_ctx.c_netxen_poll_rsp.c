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
typedef  int /*<<< orphan*/  u32 ;
struct netxen_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NXRD32 (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NX_CDRP_CRB_OFFSET ; 
 int /*<<< orphan*/  NX_CDRP_IS_RSP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NX_CDRP_RSP_OK ; 
 int /*<<< orphan*/  NX_CDRP_RSP_TIMEOUT ; 
 int NX_OS_CRB_RETRY_COUNT ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static u32
netxen_poll_rsp(struct netxen_adapter *adapter)
{
	u32 rsp = NX_CDRP_RSP_OK;
	int	timeout = 0;

	do {
		/* give atleast 1ms for firmware to respond */
		msleep(1);

		if (++timeout > NX_OS_CRB_RETRY_COUNT)
			return NX_CDRP_RSP_TIMEOUT;

		rsp = NXRD32(adapter, NX_CDRP_CRB_OFFSET);
	} while (!NX_CDRP_IS_RSP(rsp));

	return rsp;
}