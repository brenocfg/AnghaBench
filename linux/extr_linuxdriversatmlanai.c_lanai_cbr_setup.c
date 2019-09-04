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
struct lanai_dev {int /*<<< orphan*/  conf2; TYPE_1__* cbrvcc; } ;
struct TYPE_2__ {int /*<<< orphan*/  vci; int /*<<< orphan*/  qos; } ;

/* Variables and functions */
 int /*<<< orphan*/  CBR_ICG_Reg ; 
 int /*<<< orphan*/  CBR_PTR_Reg ; 
 int /*<<< orphan*/  CONFIG2_CBR_ENABLE ; 
 int /*<<< orphan*/  conf2_write (struct lanai_dev*) ; 
 int /*<<< orphan*/  pcr_to_cbricg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_write (struct lanai_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void lanai_cbr_setup(struct lanai_dev *lanai)
{
	reg_write(lanai, pcr_to_cbricg(&lanai->cbrvcc->qos), CBR_ICG_Reg);
	reg_write(lanai, lanai->cbrvcc->vci, CBR_PTR_Reg);
	lanai->conf2 |= CONFIG2_CBR_ENABLE;
	conf2_write(lanai);
}