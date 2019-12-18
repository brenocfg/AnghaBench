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
 unsigned long DBELL_ADDR ; 
 unsigned long DBELL_RNWR ; 
 scalar_t__ DOORBELL ; 
 int HZ ; 
 scalar_t__ MBOX_PEEK_POKE ; 
 unsigned long c4inmeml (scalar_t__) ; 
 int /*<<< orphan*/  c4outmeml (scalar_t__,unsigned long) ; 
 scalar_t__ wait_for_doorbell (TYPE_1__*,int) ; 

__attribute__((used)) static int c4_peek(avmcard *card,  unsigned long off, unsigned long *valuep)
{
	if (wait_for_doorbell(card, HZ / 10) < 0)
		return -1;

	c4outmeml(card->mbase + MBOX_PEEK_POKE, off);
	c4outmeml(card->mbase + DOORBELL, DBELL_RNWR | DBELL_ADDR);

	if (wait_for_doorbell(card, HZ / 10) < 0)
		return -1;

	*valuep = c4inmeml(card->mbase + MBOX_PEEK_POKE);

	return 0;
}