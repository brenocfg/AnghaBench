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
typedef  int /*<<< orphan*/  u32 ;
struct etnaviv_cmdbuf {int user_size; int size; scalar_t__ vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static inline void OUT(struct etnaviv_cmdbuf *buffer, u32 data)
{
	u32 *vaddr = (u32 *)buffer->vaddr;

	BUG_ON(buffer->user_size >= buffer->size);

	vaddr[buffer->user_size / 4] = data;
	buffer->user_size += 4;
}