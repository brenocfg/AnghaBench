#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  intr_coal_div; int /*<<< orphan*/  intr_coal_mult; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;
struct ionic {TYPE_2__ ident; } ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 ionic_coal_hw_to_usec(struct ionic *ionic, u32 units)
{
	u32 mult = le32_to_cpu(ionic->ident.dev.intr_coal_mult);
	u32 div = le32_to_cpu(ionic->ident.dev.intr_coal_div);

	/* Div-by-zero should never be an issue, but check anyway */
	if (!div || !mult)
		return 0;

	/* Convert from device units to usec */
	return (units * div) / mult;
}