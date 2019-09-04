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
typedef  int u16 ;
struct si476x_core {int revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  SI476X_REVISION_A10 130 
#define  SI476X_REVISION_A20 129 
#define  SI476X_REVISION_A30 128 

__attribute__((used)) static bool si476x_core_is_readonly_property(struct si476x_core *core,
					     u16 property)
{
	BUG_ON(core->revision > SI476X_REVISION_A30 ||
	       core->revision == -1);

	switch (core->revision) {
	case SI476X_REVISION_A10:
		return (property == 0x3200);
	case SI476X_REVISION_A20:
		return (property == 0x1006 ||
			property == 0x2210 ||
			property == 0x3200);
	case SI476X_REVISION_A30:
		return false;
	}

	return false;
}