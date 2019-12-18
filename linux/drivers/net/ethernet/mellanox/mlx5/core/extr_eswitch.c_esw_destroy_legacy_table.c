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
struct mlx5_eswitch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  esw_cleanup_vepa_rules (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_destroy_legacy_fdb_table (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_destroy_legacy_vepa_table (struct mlx5_eswitch*) ; 

__attribute__((used)) static void esw_destroy_legacy_table(struct mlx5_eswitch *esw)
{
	esw_cleanup_vepa_rules(esw);
	esw_destroy_legacy_fdb_table(esw);
	esw_destroy_legacy_vepa_table(esw);
}