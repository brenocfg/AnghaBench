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
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_hba {int /*<<< orphan*/  cfg_log_verbose; } ;

/* Variables and functions */

__attribute__((used)) static void
lpfc_hba_log_verbose_init(struct lpfc_hba *phba, uint32_t verbose)
{
	phba->cfg_log_verbose = verbose;
}