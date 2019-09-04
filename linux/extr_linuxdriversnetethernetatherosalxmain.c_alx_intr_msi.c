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
struct alx_priv {int /*<<< orphan*/  hw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALX_ISR ; 
 int /*<<< orphan*/  alx_intr_handle (struct alx_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alx_read_mem32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t alx_intr_msi(int irq, void *data)
{
	struct alx_priv *alx = data;

	return alx_intr_handle(alx, alx_read_mem32(&alx->hw, ALX_ISR));
}