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

/* Variables and functions */
 int /*<<< orphan*/  dma_free_pagelist (struct page*) ; 

__attribute__((used)) static void iova_entry_free(unsigned long data)
{
	struct page *freelist = (struct page *)data;

	dma_free_pagelist(freelist);
}