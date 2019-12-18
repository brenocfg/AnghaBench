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
struct TYPE_2__ {int /*<<< orphan*/  legacy; } ;
struct mlx5_eswitch {TYPE_1__ fdb_table; } ;
struct legacy_fdb {int dummy; } ;

/* Variables and functions */
 int esw_create_legacy_fdb_table (struct mlx5_eswitch*) ; 
 int esw_create_legacy_vepa_table (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_destroy_legacy_vepa_table (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int esw_create_legacy_table(struct mlx5_eswitch *esw)
{
	int err;

	memset(&esw->fdb_table.legacy, 0, sizeof(struct legacy_fdb));

	err = esw_create_legacy_vepa_table(esw);
	if (err)
		return err;

	err = esw_create_legacy_fdb_table(esw);
	if (err)
		esw_destroy_legacy_vepa_table(esw);

	return err;
}