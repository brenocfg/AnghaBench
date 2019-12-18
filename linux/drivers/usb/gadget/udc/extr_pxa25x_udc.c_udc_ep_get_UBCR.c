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
struct pxa25x_ep {int /*<<< orphan*/  regoff_ubcr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  udc_get_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 udc_ep_get_UBCR(struct pxa25x_ep *ep)
{
	return udc_get_reg(ep->dev, ep->regoff_ubcr);
}