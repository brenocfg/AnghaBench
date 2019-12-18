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
typedef  int /*<<< orphan*/  u8 ;
struct iscsi_task {struct iscsi_iser_task* dd_data; } ;
struct iscsi_iser_task {scalar_t__* dir; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  enum iser_data_dir { ____Placeholder_iser_data_dir } iser_data_dir ;

/* Variables and functions */
 size_t ISER_DIR_IN ; 
 size_t ISER_DIR_OUT ; 
 int /*<<< orphan*/  iser_check_task_pi_status (struct iscsi_iser_task*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8
iscsi_iser_check_protection(struct iscsi_task *task, sector_t *sector)
{
	struct iscsi_iser_task *iser_task = task->dd_data;
	enum iser_data_dir dir = iser_task->dir[ISER_DIR_IN] ?
					ISER_DIR_IN : ISER_DIR_OUT;

	return iser_check_task_pi_status(iser_task, dir, sector);
}