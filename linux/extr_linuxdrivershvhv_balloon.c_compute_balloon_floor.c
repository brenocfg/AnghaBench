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
 int PAGE_SHIFT ; 
 int totalram_pages ; 

__attribute__((used)) static unsigned long compute_balloon_floor(void)
{
	unsigned long min_pages;
#define MB2PAGES(mb) ((mb) << (20 - PAGE_SHIFT))
	/* Simple continuous piecewiese linear function:
	 *  max MiB -> min MiB  gradient
	 *       0         0
	 *      16        16
	 *      32        24
	 *     128        72    (1/2)
	 *     512       168    (1/4)
	 *    2048       360    (1/8)
	 *    8192       744    (1/16)
	 *   32768      1512	(1/32)
	 */
	if (totalram_pages < MB2PAGES(128))
		min_pages = MB2PAGES(8) + (totalram_pages >> 1);
	else if (totalram_pages < MB2PAGES(512))
		min_pages = MB2PAGES(40) + (totalram_pages >> 2);
	else if (totalram_pages < MB2PAGES(2048))
		min_pages = MB2PAGES(104) + (totalram_pages >> 3);
	else if (totalram_pages < MB2PAGES(8192))
		min_pages = MB2PAGES(232) + (totalram_pages >> 4);
	else
		min_pages = MB2PAGES(488) + (totalram_pages >> 5);
#undef MB2PAGES
	return min_pages;
}