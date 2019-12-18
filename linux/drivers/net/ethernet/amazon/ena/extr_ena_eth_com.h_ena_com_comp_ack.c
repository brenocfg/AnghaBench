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
typedef  scalar_t__ u16 ;
struct ena_com_io_sq {int /*<<< orphan*/  next_to_comp; } ;

/* Variables and functions */

__attribute__((used)) static inline void ena_com_comp_ack(struct ena_com_io_sq *io_sq, u16 elem)
{
	io_sq->next_to_comp += elem;
}