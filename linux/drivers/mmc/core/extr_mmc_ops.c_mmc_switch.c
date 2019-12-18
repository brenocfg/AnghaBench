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
typedef  int /*<<< orphan*/  u8 ;
struct mmc_card {int dummy; } ;

/* Variables and functions */
 int __mmc_switch (struct mmc_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int,int,int) ; 

int mmc_switch(struct mmc_card *card, u8 set, u8 index, u8 value,
		unsigned int timeout_ms)
{
	return __mmc_switch(card, set, index, value, timeout_ms, 0,
			true, true, false);
}