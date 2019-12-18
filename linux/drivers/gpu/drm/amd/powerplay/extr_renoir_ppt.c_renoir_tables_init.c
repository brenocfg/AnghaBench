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
struct smu_table_context {int /*<<< orphan*/  clocks_table; } ;
struct smu_table {int dummy; } ;
struct smu_context {struct smu_table_context smu_table; } ;
typedef  int /*<<< orphan*/  Watermarks_t ;
typedef  int /*<<< orphan*/  SmuMetrics_t ;
typedef  int /*<<< orphan*/  DpmClocks_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SMU_TABLE_DPMCLOCKS ; 
 int /*<<< orphan*/  SMU_TABLE_INIT (struct smu_table*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMU_TABLE_SMU_METRICS ; 
 int /*<<< orphan*/  SMU_TABLE_WATERMARKS ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int renoir_tables_init(struct smu_context *smu, struct smu_table *tables)
{
	struct smu_table_context *smu_table = &smu->smu_table;

	SMU_TABLE_INIT(tables, SMU_TABLE_WATERMARKS, sizeof(Watermarks_t),
		PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_DPMCLOCKS, sizeof(DpmClocks_t),
		PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_SMU_METRICS, sizeof(SmuMetrics_t),
		PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);

	smu_table->clocks_table = kzalloc(sizeof(DpmClocks_t), GFP_KERNEL);
	if (!smu_table->clocks_table)
		return -ENOMEM;

	return 0;
}