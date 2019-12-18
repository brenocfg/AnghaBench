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
struct alcor_pci_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU6601_MS_INT_ENABLE ; 
 int /*<<< orphan*/  alcor_write32 (struct alcor_pci_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void alcor_mask_ms_irqs(struct alcor_pci_priv *priv)
{
	alcor_write32(priv, 0, AU6601_MS_INT_ENABLE);
}