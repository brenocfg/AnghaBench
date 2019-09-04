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
struct mtdswap_dev {scalar_t__ pages_per_eblk; } ;

/* Variables and functions */
 scalar_t__ mtdswap_free_page_cnt (struct mtdswap_dev*) ; 

__attribute__((used)) static unsigned int mtdswap_enough_free_pages(struct mtdswap_dev *d)
{
	return mtdswap_free_page_cnt(d) > d->pages_per_eblk;
}