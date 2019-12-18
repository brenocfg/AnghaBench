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
struct page {int dummy; } ;
struct ftmac100_rxdes {scalar_t__ rxdes3; } ;

/* Variables and functions */

__attribute__((used)) static struct page *ftmac100_rxdes_get_page(struct ftmac100_rxdes *rxdes)
{
	return (struct page *)rxdes->rxdes3;
}