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
struct lpfc_hba {scalar_t__ link_state; } ;

/* Variables and functions */
 scalar_t__ LPFC_CLEAR_LA ; 
 scalar_t__ LPFC_HBA_READY ; 
 scalar_t__ LPFC_LINK_UP ; 

__attribute__((used)) static inline int
lpfc_is_link_up(struct lpfc_hba *phba)
{
	return  phba->link_state == LPFC_LINK_UP ||
		phba->link_state == LPFC_CLEAR_LA ||
		phba->link_state == LPFC_HBA_READY;
}