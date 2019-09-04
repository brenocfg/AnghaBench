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

/* Variables and functions */
 unsigned long DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_KEY_DATA_SIZE ; 

unsigned long page_key_additional_pages(unsigned long pages)
{
	return DIV_ROUND_UP(pages, PAGE_KEY_DATA_SIZE);
}