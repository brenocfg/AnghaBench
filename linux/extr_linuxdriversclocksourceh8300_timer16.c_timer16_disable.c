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
struct timer16_priv {int cs_enabled; scalar_t__ mapcommon; int /*<<< orphan*/  enb; int /*<<< orphan*/  ovie; } ;
struct clocksource {int dummy; } ;

/* Variables and functions */
 scalar_t__ TISRC ; 
 scalar_t__ TSTR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bclr (int /*<<< orphan*/ ,scalar_t__) ; 
 struct timer16_priv* cs_to_priv (struct clocksource*) ; 

__attribute__((used)) static void timer16_disable(struct clocksource *cs)
{
	struct timer16_priv *p = cs_to_priv(cs);

	WARN_ON(!p->cs_enabled);

	bclr(p->ovie, p->mapcommon + TISRC);
	bclr(p->enb, p->mapcommon + TSTR);

	p->cs_enabled = false;
}