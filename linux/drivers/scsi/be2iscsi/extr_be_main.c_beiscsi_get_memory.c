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
struct beiscsi_hba {int dummy; } ;

/* Variables and functions */
 int beiscsi_alloc_mem (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_find_mem_req (struct beiscsi_hba*) ; 

__attribute__((used)) static int beiscsi_get_memory(struct beiscsi_hba *phba)
{
	beiscsi_find_mem_req(phba);
	return beiscsi_alloc_mem(phba);
}