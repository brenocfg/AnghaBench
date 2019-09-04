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
struct macio_chip {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 long ENODEV ; 
 int /*<<< orphan*/  HEATHROW_FCR ; 
 int /*<<< orphan*/  HEATHROW_MBCR ; 
 int HRW_MESH_ENABLE ; 
 int /*<<< orphan*/  LOCK (unsigned long) ; 
 int /*<<< orphan*/  MACIO_BIC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MACIO_BIS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MACIO_IN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK (unsigned long) ; 
 struct macio_chip* macio_find (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macio_unknown ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static long heathrow_mesh_enable(struct device_node *node, long param,
				 long value)
{
	struct macio_chip*	macio;
	unsigned long		flags;

	macio = macio_find(node, macio_unknown);
	if (!macio)
		return -ENODEV;
	LOCK(flags);
	/* Set clear mesh cell enable */
	if (value)
		MACIO_BIS(HEATHROW_FCR, HRW_MESH_ENABLE);
	else
		MACIO_BIC(HEATHROW_FCR, HRW_MESH_ENABLE);
	(void)MACIO_IN32(HEATHROW_FCR);
	udelay(10);
	/* Set/Clear termination power */
	if (value)
		MACIO_BIC(HEATHROW_MBCR, 0x04000000);
	else
		MACIO_BIS(HEATHROW_MBCR, 0x04000000);
	(void)MACIO_IN32(HEATHROW_MBCR);
	udelay(10);
	UNLOCK(flags);

	return 0;
}