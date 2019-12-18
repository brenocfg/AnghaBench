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
struct dwc2_hsotg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dwc2_readl_rep(struct dwc2_hsotg *hsotg, u32 offset,
				  void *buffer, unsigned int count)
{
	if (count) {
		u32 *buf = buffer;

		do {
			u32 x = dwc2_readl(hsotg, offset);
			*buf++ = x;
		} while (--count);
	}
}