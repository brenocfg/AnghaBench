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
typedef  int u32 ;
struct mlx5_db_pgdir {int /*<<< orphan*/  bitmap; int /*<<< orphan*/  db_page; int /*<<< orphan*/  db_dma; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  bitmap_fill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_zalloc (int,int /*<<< orphan*/ ) ; 
 int cache_line_size () ; 
 int /*<<< orphan*/  kfree (struct mlx5_db_pgdir*) ; 
 struct mlx5_db_pgdir* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_dma_zalloc_coherent_node (struct mlx5_core_dev*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct mlx5_db_pgdir *mlx5_alloc_db_pgdir(struct mlx5_core_dev *dev,
						 int node)
{
	u32 db_per_page = PAGE_SIZE / cache_line_size();
	struct mlx5_db_pgdir *pgdir;

	pgdir = kzalloc(sizeof(*pgdir), GFP_KERNEL);
	if (!pgdir)
		return NULL;

	pgdir->bitmap = bitmap_zalloc(db_per_page, GFP_KERNEL);
	if (!pgdir->bitmap) {
		kfree(pgdir);
		return NULL;
	}

	bitmap_fill(pgdir->bitmap, db_per_page);

	pgdir->db_page = mlx5_dma_zalloc_coherent_node(dev, PAGE_SIZE,
						       &pgdir->db_dma, node);
	if (!pgdir->db_page) {
		bitmap_free(pgdir->bitmap);
		kfree(pgdir);
		return NULL;
	}

	return pgdir;
}