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
struct t4_sq {int /*<<< orphan*/  memsize; int /*<<< orphan*/  dma_addr; } ;
struct c4iw_rdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  c4iw_ocqp_pool_free (struct c4iw_rdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dealloc_oc_sq(struct c4iw_rdev *rdev, struct t4_sq *sq)
{
	c4iw_ocqp_pool_free(rdev, sq->dma_addr, sq->memsize);
}