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
struct smu_table_context {scalar_t__ metrics_time; int /*<<< orphan*/  metrics_table; } ;
struct smu_table {int dummy; } ;
struct smu_context {struct smu_table_context smu_table; } ;
typedef  int /*<<< orphan*/  Watermarks_t ;
typedef  int /*<<< orphan*/  SmuMetrics_t ;
typedef  int /*<<< orphan*/  PPTable_t ;
typedef  int /*<<< orphan*/  OverDriveTable_t ;
typedef  int /*<<< orphan*/  DpmActivityMonitorCoeffInt_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int SMU11_TOOL_SIZE ; 
 int /*<<< orphan*/  SMU_TABLE_ACTIVITY_MONITOR_COEFF ; 
 int /*<<< orphan*/  SMU_TABLE_INIT (struct smu_table*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMU_TABLE_OVERDRIVE ; 
 int /*<<< orphan*/  SMU_TABLE_PMSTATUSLOG ; 
 int /*<<< orphan*/  SMU_TABLE_PPTABLE ; 
 int /*<<< orphan*/  SMU_TABLE_SMU_METRICS ; 
 int /*<<< orphan*/  SMU_TABLE_WATERMARKS ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int navi10_tables_init(struct smu_context *smu, struct smu_table *tables)
{
	struct smu_table_context *smu_table = &smu->smu_table;

	SMU_TABLE_INIT(tables, SMU_TABLE_PPTABLE, sizeof(PPTable_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_WATERMARKS, sizeof(Watermarks_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_SMU_METRICS, sizeof(SmuMetrics_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_OVERDRIVE, sizeof(OverDriveTable_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_PMSTATUSLOG, SMU11_TOOL_SIZE,
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_ACTIVITY_MONITOR_COEFF,
		       sizeof(DpmActivityMonitorCoeffInt_t), PAGE_SIZE,
		       AMDGPU_GEM_DOMAIN_VRAM);

	smu_table->metrics_table = kzalloc(sizeof(SmuMetrics_t), GFP_KERNEL);
	if (!smu_table->metrics_table)
		return -ENOMEM;
	smu_table->metrics_time = 0;

	return 0;
}