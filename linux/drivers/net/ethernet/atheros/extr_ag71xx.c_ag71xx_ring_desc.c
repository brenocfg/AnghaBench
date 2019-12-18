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
struct ag71xx_ring {int /*<<< orphan*/ * descs_cpu; } ;
struct ag71xx_desc {int dummy; } ;

/* Variables and functions */
 int AG71XX_DESC_SIZE ; 

__attribute__((used)) static struct ag71xx_desc *ag71xx_ring_desc(struct ag71xx_ring *ring, int idx)
{
	return (struct ag71xx_desc *)&ring->descs_cpu[idx * AG71XX_DESC_SIZE];
}