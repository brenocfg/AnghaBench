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
struct pblk {int capacity; } ;
typedef  int sector_t ;

/* Variables and functions */
 int NR_PHY_IN_LOG ; 

__attribute__((used)) static sector_t pblk_capacity(void *private)
{
	struct pblk *pblk = private;

	return pblk->capacity * NR_PHY_IN_LOG;
}