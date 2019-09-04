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
struct tpu_priv {int cs_enabled; scalar_t__ mapbase2; scalar_t__ mapbase1; } ;
struct clocksource {int dummy; } ;

/* Variables and functions */
 scalar_t__ TCR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct tpu_priv* cs_to_priv (struct clocksource*) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tpu_clocksource_disable(struct clocksource *cs)
{
	struct tpu_priv *p = cs_to_priv(cs);

	WARN_ON(!p->cs_enabled);

	iowrite8(0, p->mapbase1 + TCR);
	iowrite8(0, p->mapbase2 + TCR);
	p->cs_enabled = false;
}