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

/* Variables and functions */
 size_t CAAM_CMD_SZ ; 
 int HDR_START_IDX_SHIFT ; 
 int /*<<< orphan*/  init_job_desc (int* const,int) ; 

__attribute__((used)) static inline void init_job_desc_pdb(u32 * const desc, u32 options,
				     size_t pdb_bytes)
{
	u32 pdb_len = (pdb_bytes + CAAM_CMD_SZ - 1) / CAAM_CMD_SZ;

	init_job_desc(desc, (((pdb_len + 1) << HDR_START_IDX_SHIFT)) | options);
}