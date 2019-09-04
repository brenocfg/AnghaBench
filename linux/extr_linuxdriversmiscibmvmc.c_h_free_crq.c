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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 long H_BUSY ; 
 int /*<<< orphan*/  H_FREE_CRQ ; 
 scalar_t__ H_IS_LONG_BUSY (long) ; 
 int /*<<< orphan*/  get_longbusy_msecs (long) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 long plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void h_free_crq(uint32_t unit_address)
{
	long rc = 0;

	do {
		if (H_IS_LONG_BUSY(rc))
			msleep(get_longbusy_msecs(rc));

		rc = plpar_hcall_norets(H_FREE_CRQ, unit_address);
	} while ((rc == H_BUSY) || (H_IS_LONG_BUSY(rc)));
}