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
struct edma_cc {int dummy; } ;

/* Variables and functions */
 unsigned int edma_read (struct edma_cc*,int) ; 

__attribute__((used)) static inline unsigned int edma_read_array(struct edma_cc *ecc, int offset,
					   int i)
{
	return edma_read(ecc, offset + (i << 2));
}