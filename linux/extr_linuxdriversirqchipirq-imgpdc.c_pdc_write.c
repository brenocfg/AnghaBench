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
struct pdc_intc_priv {scalar_t__ pdc_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (unsigned int,scalar_t__) ; 

__attribute__((used)) static void pdc_write(struct pdc_intc_priv *priv, unsigned int reg_offs,
		      unsigned int data)
{
	iowrite32(data, priv->pdc_base + reg_offs);
}