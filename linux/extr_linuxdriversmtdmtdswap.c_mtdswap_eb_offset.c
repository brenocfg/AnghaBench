#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct swap_eb {int dummy; } ;
struct mtdswap_dev {TYPE_1__* mtd; struct swap_eb* eb_data; } ;
typedef  int loff_t ;
struct TYPE_2__ {int erasesize; } ;

/* Variables and functions */

__attribute__((used)) static loff_t mtdswap_eb_offset(struct mtdswap_dev *d, struct swap_eb *eb)
{
	return (loff_t)(eb - d->eb_data) * d->mtd->erasesize;
}