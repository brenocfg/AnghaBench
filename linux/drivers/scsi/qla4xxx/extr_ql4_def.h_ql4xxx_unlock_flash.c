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
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL4010_FLASH_SEM_MASK ; 
 int /*<<< orphan*/  QL4022_FLASH_SEM_MASK ; 
 scalar_t__ is_qla4010 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  ql4xxx_sem_unlock (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ql4xxx_unlock_flash(struct scsi_qla_host *a)
{
	if (is_qla4010(a))
		ql4xxx_sem_unlock(a, QL4010_FLASH_SEM_MASK);
	else
		ql4xxx_sem_unlock(a, QL4022_FLASH_SEM_MASK);
}