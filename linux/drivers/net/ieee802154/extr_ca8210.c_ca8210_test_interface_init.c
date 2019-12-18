#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ca8210_test {int /*<<< orphan*/  up_fifo; int /*<<< orphan*/  readq; int /*<<< orphan*/  ca8210_dfs_spi_int; } ;
struct ca8210_priv {TYPE_2__* spi; struct ca8210_test test; } ;
typedef  int /*<<< orphan*/  node_name ;
struct TYPE_4__ {int chip_select; TYPE_1__* master; } ;
struct TYPE_3__ {int bus_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA8210_TEST_INT_FIFO_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ *,struct ca8210_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_symlink (char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int kfifo_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int /*<<< orphan*/  test_int_fops ; 

__attribute__((used)) static int ca8210_test_interface_init(struct ca8210_priv *priv)
{
	struct ca8210_test *test = &priv->test;
	char node_name[32];

	snprintf(
		node_name,
		sizeof(node_name),
		"ca8210@%d_%d",
		priv->spi->master->bus_num,
		priv->spi->chip_select
	);

	test->ca8210_dfs_spi_int = debugfs_create_file(
		node_name,
		0600, /* S_IRUSR | S_IWUSR */
		NULL,
		priv,
		&test_int_fops
	);

	debugfs_create_symlink("ca8210", NULL, node_name);
	init_waitqueue_head(&test->readq);
	return kfifo_alloc(
		&test->up_fifo,
		CA8210_TEST_INT_FIFO_SIZE,
		GFP_KERNEL
	);
}