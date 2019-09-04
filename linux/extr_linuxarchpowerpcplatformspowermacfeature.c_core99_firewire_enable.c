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
struct macio_chip {scalar_t__ type; int flags; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 long ENODEV ; 
 int /*<<< orphan*/  LOCK (unsigned long) ; 
 int MACIO_FLAG_FW_SUPPORTED ; 
 int /*<<< orphan*/  UNI_N_CLOCK_CNTL ; 
 int /*<<< orphan*/  UNI_N_CLOCK_CNTL_FW ; 
 int /*<<< orphan*/  UNLOCK (unsigned long) ; 
 int /*<<< orphan*/  UN_BIC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UN_BIS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UN_IN (int /*<<< orphan*/ ) ; 
 struct macio_chip* macio_chips ; 
 scalar_t__ macio_intrepid ; 
 scalar_t__ macio_keylargo ; 
 scalar_t__ macio_pangea ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static long
core99_firewire_enable(struct device_node *node, long param, long value)
{
	unsigned long flags;
	struct macio_chip *macio;

	macio = &macio_chips[0];
	if (macio->type != macio_keylargo && macio->type != macio_pangea &&
	    macio->type != macio_intrepid)
		return -ENODEV;
	if (!(macio->flags & MACIO_FLAG_FW_SUPPORTED))
		return -ENODEV;

	LOCK(flags);
	if (value) {
		UN_BIS(UNI_N_CLOCK_CNTL, UNI_N_CLOCK_CNTL_FW);
		(void)UN_IN(UNI_N_CLOCK_CNTL);
	} else {
		UN_BIC(UNI_N_CLOCK_CNTL, UNI_N_CLOCK_CNTL_FW);
		(void)UN_IN(UNI_N_CLOCK_CNTL);
	}
	UNLOCK(flags);
	mdelay(1);

	return 0;
}