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
struct mlx4_db_pgdir {int /*<<< orphan*/  db_page; int /*<<< orphan*/  db_dma; int /*<<< orphan*/  order1; int /*<<< orphan*/ * bits; int /*<<< orphan*/  order0; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX4_DB_PER_PAGE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  bitmap_fill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx4_db_pgdir*) ; 
 struct mlx4_db_pgdir* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlx4_db_pgdir *mlx4_alloc_db_pgdir(struct device *dma_device)
{
	struct mlx4_db_pgdir *pgdir;

	pgdir = kzalloc(sizeof(*pgdir), GFP_KERNEL);
	if (!pgdir)
		return NULL;

	bitmap_fill(pgdir->order1, MLX4_DB_PER_PAGE / 2);
	pgdir->bits[0] = pgdir->order0;
	pgdir->bits[1] = pgdir->order1;
	pgdir->db_page = dma_alloc_coherent(dma_device, PAGE_SIZE,
					    &pgdir->db_dma, GFP_KERNEL);
	if (!pgdir->db_page) {
		kfree(pgdir);
		return NULL;
	}

	return pgdir;
}