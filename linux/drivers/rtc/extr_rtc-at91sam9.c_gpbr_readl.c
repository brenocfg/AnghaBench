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
struct sam9_rtc {int /*<<< orphan*/  gpbr_offset; int /*<<< orphan*/  gpbr; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static inline unsigned int gpbr_readl(struct sam9_rtc *rtc)
{
	unsigned int val;

	regmap_read(rtc->gpbr, rtc->gpbr_offset, &val);

	return val;
}