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
typedef  int u8 ;
struct macio_chip {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; struct device_node* of_node; } ;

/* Variables and functions */
 long ENODEV ; 
 int /*<<< orphan*/  KEYLARGO_FCR2 ; 
 int KEYLARGO_GPIO_OUTOUT_DATA ; 
 int KEYLARGO_GPIO_OUTPUT_ENABLE ; 
 int /*<<< orphan*/  KL2_ALT_DATA_OUT ; 
 int /*<<< orphan*/  KL_GPIO_MODEM_RESET ; 
 int /*<<< orphan*/  LOCK (unsigned long) ; 
 int /*<<< orphan*/  MACIO_BIC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACIO_BIS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACIO_IN32 (int /*<<< orphan*/ ) ; 
 int MACIO_IN8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACIO_OUT8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UNLOCK (unsigned long) ; 
 TYPE_1__* macio_chips ; 
 struct macio_chip* macio_find (struct device_node*,int /*<<< orphan*/ ) ; 
 scalar_t__ macio_keylargo ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static long
core99_modem_enable(struct device_node *node, long param, long value)
{
	struct macio_chip*	macio;
	u8			gpio;
	unsigned long		flags;

	/* Hack for internal USB modem */
	if (node == NULL) {
		if (macio_chips[0].type != macio_keylargo)
			return -ENODEV;
		node = macio_chips[0].of_node;
	}
	macio = macio_find(node, 0);
	if (!macio)
		return -ENODEV;
	gpio = MACIO_IN8(KL_GPIO_MODEM_RESET);
	gpio |= KEYLARGO_GPIO_OUTPUT_ENABLE;
	gpio &= ~KEYLARGO_GPIO_OUTOUT_DATA;

	if (!value) {
		LOCK(flags);
		MACIO_OUT8(KL_GPIO_MODEM_RESET, gpio);
		UNLOCK(flags);
		(void)MACIO_IN8(KL_GPIO_MODEM_RESET);
		mdelay(250);
	}
	LOCK(flags);
	if (value) {
		MACIO_BIC(KEYLARGO_FCR2, KL2_ALT_DATA_OUT);
		UNLOCK(flags);
		(void)MACIO_IN32(KEYLARGO_FCR2);
		mdelay(250);
	} else {
		MACIO_BIS(KEYLARGO_FCR2, KL2_ALT_DATA_OUT);
		UNLOCK(flags);
	}
	if (value) {
		LOCK(flags);
		MACIO_OUT8(KL_GPIO_MODEM_RESET, gpio | KEYLARGO_GPIO_OUTOUT_DATA);
		(void)MACIO_IN8(KL_GPIO_MODEM_RESET);
		UNLOCK(flags); mdelay(250); LOCK(flags);
		MACIO_OUT8(KL_GPIO_MODEM_RESET, gpio);
		(void)MACIO_IN8(KL_GPIO_MODEM_RESET);
		UNLOCK(flags); mdelay(250); LOCK(flags);
		MACIO_OUT8(KL_GPIO_MODEM_RESET, gpio | KEYLARGO_GPIO_OUTOUT_DATA);
		(void)MACIO_IN8(KL_GPIO_MODEM_RESET);
		UNLOCK(flags); mdelay(250);
	}
	return 0;
}