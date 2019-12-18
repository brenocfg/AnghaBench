#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct mlx4_eqe {int dummy; } ;
struct mlx4_eq {int nent; TYPE_1__* page_list; } ;
struct TYPE_2__ {struct mlx4_eqe* buf; } ;

/* Variables and functions */
 unsigned long MLX4_EQ_ENTRY_SIZE ; 
 unsigned long PAGE_SIZE ; 

__attribute__((used)) static struct mlx4_eqe *get_eqe(struct mlx4_eq *eq, u32 entry, u8 eqe_factor,
				u8 eqe_size)
{
	/* (entry & (eq->nent - 1)) gives us a cyclic array */
	unsigned long offset = (entry & (eq->nent - 1)) * eqe_size;
	/* CX3 is capable of extending the EQE from 32 to 64 bytes with
	 * strides of 64B,128B and 256B.
	 * When 64B EQE is used, the first (in the lower addresses)
	 * 32 bytes in the 64 byte EQE are reserved and the next 32 bytes
	 * contain the legacy EQE information.
	 * In all other cases, the first 32B contains the legacy EQE info.
	 */
	return eq->page_list[offset / PAGE_SIZE].buf + (offset + (eqe_factor ? MLX4_EQ_ENTRY_SIZE : 0)) % PAGE_SIZE;
}