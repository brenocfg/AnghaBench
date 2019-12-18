#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ mbase; } ;
typedef  TYPE_1__ avmcard ;

/* Variables and functions */
 scalar_t__ CHAN_1_CONTROL ; 
 scalar_t__ CHAN_2_CONTROL ; 
 int /*<<< orphan*/  DBELL_ADDR ; 
 int /*<<< orphan*/  DBELL_RESET_ARM ; 
 scalar_t__ DC21285_ARMCSR_BASE ; 
 scalar_t__ DOORBELL ; 
 int HZ ; 
 int /*<<< orphan*/  c4_poke (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int c4inmeml (scalar_t__) ; 
 int /*<<< orphan*/  c4outmeml (scalar_t__,int /*<<< orphan*/ ) ; 
 int jiffies ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  time_before (int,unsigned long) ; 

__attribute__((used)) static void c4_reset(avmcard *card)
{
	unsigned long stop;

	c4outmeml(card->mbase + DOORBELL, DBELL_RESET_ARM);

	stop = jiffies + HZ * 10;
	while (c4inmeml(card->mbase + DOORBELL) != 0xffffffff) {
		if (!time_before(jiffies, stop))
			return;
		c4outmeml(card->mbase + DOORBELL, DBELL_ADDR);
		mb();
	}

	c4_poke(card, DC21285_ARMCSR_BASE + CHAN_1_CONTROL, 0);
	c4_poke(card, DC21285_ARMCSR_BASE + CHAN_2_CONTROL, 0);
}