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
struct mlx4_en_rx_ring {scalar_t__ prod; scalar_t__ cons; } ;

/* Variables and functions */

__attribute__((used)) static bool mlx4_en_is_ring_empty(const struct mlx4_en_rx_ring *ring)
{
	return ring->prod == ring->cons;
}