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
typedef  void mlx4_cqe ;

/* Variables and functions */

__attribute__((used)) static inline struct mlx4_cqe *mlx4_en_get_cqe(void *buf, int idx, int cqe_sz)
{
	return buf + idx * cqe_sz;
}