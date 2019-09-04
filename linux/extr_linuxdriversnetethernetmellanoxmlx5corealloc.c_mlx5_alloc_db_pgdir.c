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
struct mlx5_db_pgdir {struct mlx5_db_pgdir* bitmap; int /*<<< orphan*/  db_page; int /*<<< orphan*/  db_dma; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_TO_LONGS (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  bitmap_fill (struct mlx5_db_pgdir*,int) ; 
 int cache_line_size () ; 
 struct mlx5_db_pgdir* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
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

	pgdir->bitmap = kcalloc(BITS_TO_LONGS(db_per_page),
				sizeof(unsigned long),
				GFP_KERNEL);

	if (!pgdir->bitmap) {
		kfree(pgdir);
		return NULL;
	}

	bitmap_fill(pgdir->bitmap, db_per_page);

	pgdir->db_page = mlx5_dma_zalloc_coherent_node(dev, PAGE_SIZE,
						       &pgdir->db_dma, node);
	if (!pgdir->db_page) {
		kfree(pgdir->bitmap);
		kfree(pgdir);
		return NULL;
	}

	return pgdir;
}