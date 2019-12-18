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
typedef  int /*<<< orphan*/  u8 ;
struct cudbg_qdesc_entry {int data_size; } ;

/* Variables and functions */

__attribute__((used)) static inline
struct cudbg_qdesc_entry *cudbg_next_qdesc(struct cudbg_qdesc_entry *e)
{
	return (struct cudbg_qdesc_entry *)
	       ((u8 *)e + sizeof(*e) + e->data_size);
}