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
struct arcnet_local {int config; } ;

/* Variables and functions */
 int /*<<< orphan*/  COM20020_REG_W_CONFIG ; 
 int /*<<< orphan*/  COM20020_REG_W_SUBADR ; 
 int /*<<< orphan*/  arcnet_outb (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void com20020_set_subaddress(struct arcnet_local *lp,
					   int ioaddr, int val)
{
	if (val < 4) {
		lp->config = (lp->config & ~0x03) | val;
		arcnet_outb(lp->config, ioaddr, COM20020_REG_W_CONFIG);
	} else {
		arcnet_outb(val, ioaddr, COM20020_REG_W_SUBADR);
	}
}