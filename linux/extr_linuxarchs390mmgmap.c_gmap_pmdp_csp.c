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
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gmap_pmdp_clear (struct mm_struct*,unsigned long,int) ; 

void gmap_pmdp_csp(struct mm_struct *mm, unsigned long vmaddr)
{
	gmap_pmdp_clear(mm, vmaddr, 1);
}