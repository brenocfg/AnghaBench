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
struct macio_chip {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  LOCK (unsigned long) ; 
 int /*<<< orphan*/  MACIO_BIC (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACIO_BIS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACIO_IN32 (int) ; 
 int /*<<< orphan*/  UNLOCK (unsigned long) ; 
 struct macio_chip* macio_find (struct device_node*,int) ; 

__attribute__((used)) static inline int simple_feature_tweak(struct device_node *node, int type,
				       int reg, u32 mask, int value)
{
	struct macio_chip*	macio;
	unsigned long		flags;

	macio = macio_find(node, type);
	if (!macio)
		return -ENODEV;
	LOCK(flags);
	if (value)
		MACIO_BIS(reg, mask);
	else
		MACIO_BIC(reg, mask);
	(void)MACIO_IN32(reg);
	UNLOCK(flags);

	return 0;
}