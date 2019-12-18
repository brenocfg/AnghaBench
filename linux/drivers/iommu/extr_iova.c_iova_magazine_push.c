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
struct iova_magazine {unsigned long* pfns; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iova_magazine_full (struct iova_magazine*) ; 

__attribute__((used)) static void iova_magazine_push(struct iova_magazine *mag, unsigned long pfn)
{
	BUG_ON(iova_magazine_full(mag));

	mag->pfns[mag->size++] = pfn;
}