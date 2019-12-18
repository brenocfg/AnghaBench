#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hostap_plx_priv {int cor_offset; int /*<<< orphan*/ * attr_mem; } ;
struct TYPE_3__ {struct hostap_plx_priv* hw_priv; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 unsigned char COR_SRESET ; 
 unsigned char inb (int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outb (unsigned char,int) ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (unsigned char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prism2_plx_genesis_reset(local_info_t *local, int hcr)
{
	unsigned char corsave;
	struct hostap_plx_priv *hw_priv = local->hw_priv;

	if (hw_priv->attr_mem == NULL) {
		/* TMD7160 - COR at card's first I/O addr */
		corsave = inb(hw_priv->cor_offset);
		outb(corsave | COR_SRESET, hw_priv->cor_offset);
		mdelay(10);
		outb(hcr, hw_priv->cor_offset + 2);
		mdelay(10);
		outb(corsave & ~COR_SRESET, hw_priv->cor_offset);
		mdelay(10);
	} else {
		/* PLX9052 */
		corsave = readb(hw_priv->attr_mem + hw_priv->cor_offset);
		writeb(corsave | COR_SRESET,
		       hw_priv->attr_mem + hw_priv->cor_offset);
		mdelay(10);
		writeb(hcr, hw_priv->attr_mem + hw_priv->cor_offset + 2);
		mdelay(10);
		writeb(corsave & ~COR_SRESET,
		       hw_priv->attr_mem + hw_priv->cor_offset);
		mdelay(10);
	}
}