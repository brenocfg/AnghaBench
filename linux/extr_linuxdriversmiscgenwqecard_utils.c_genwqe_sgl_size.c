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
struct sg_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int roundup (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int genwqe_sgl_size(int num_pages)
{
	int len, num_tlb = num_pages / 7;

	len = sizeof(struct sg_entry) * (num_pages+num_tlb + 1);
	return roundup(len, PAGE_SIZE);
}