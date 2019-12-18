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
typedef  int /*<<< orphan*/  u32 ;
struct alcor_pci_priv {scalar_t__ iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,scalar_t__) ; 

void alcor_write32be(struct alcor_pci_priv *priv, u32 val, unsigned int addr)
{
	iowrite32be(val, priv->iobase + addr);
}