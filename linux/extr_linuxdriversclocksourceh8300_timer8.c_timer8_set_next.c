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
struct timer8_priv {scalar_t__ mapbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMFA ; 
 int /*<<< orphan*/  CMIEA ; 
 scalar_t__ TCORA ; 
 scalar_t__ _8TCNT ; 
 scalar_t__ _8TCR ; 
 scalar_t__ _8TCSR ; 
 int /*<<< orphan*/  bclr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bset (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iowrite16be (int,scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static void timer8_set_next(struct timer8_priv *p, unsigned long delta)
{
	if (delta >= 0x10000)
		pr_warn("delta out of range\n");
	bclr(CMIEA, p->mapbase + _8TCR);
	iowrite16be(delta, p->mapbase + TCORA);
	iowrite16be(0x0000, p->mapbase + _8TCNT);
	bclr(CMFA, p->mapbase + _8TCSR);
	bset(CMIEA, p->mapbase + _8TCR);
}