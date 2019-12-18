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
struct tb_ring {int dummy; } ;
struct tb_nhi {int dummy; } ;

/* Variables and functions */
 struct tb_ring* tb_ring_alloc (struct tb_nhi*,int,int,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct tb_ring *tb_ring_alloc_tx(struct tb_nhi *nhi, int hop, int size,
				 unsigned int flags)
{
	return tb_ring_alloc(nhi, hop, size, true, flags, 0, 0, NULL, NULL);
}