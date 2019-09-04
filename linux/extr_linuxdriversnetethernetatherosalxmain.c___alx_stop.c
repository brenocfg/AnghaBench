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
struct alx_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  alx_free_irq (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_free_napis (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_free_rings (struct alx_priv*) ; 
 int /*<<< orphan*/  alx_halt (struct alx_priv*) ; 

__attribute__((used)) static void __alx_stop(struct alx_priv *alx)
{
	alx_halt(alx);
	alx_free_irq(alx);
	alx_free_rings(alx);
	alx_free_napis(alx);
}