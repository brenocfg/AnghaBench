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
struct lpfc_hba {int (* lpfc_sli_hbq_to_firmware ) (struct lpfc_hba*,int /*<<< orphan*/ ,struct hbq_dmabuf*) ;int /*<<< orphan*/  hbalock; } ;
struct hbq_dmabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int stub1 (struct lpfc_hba*,int /*<<< orphan*/ ,struct hbq_dmabuf*) ; 

__attribute__((used)) static int
lpfc_sli_hbq_to_firmware(struct lpfc_hba *phba, uint32_t hbqno,
			 struct hbq_dmabuf *hbq_buf)
{
	lockdep_assert_held(&phba->hbalock);
	return phba->lpfc_sli_hbq_to_firmware(phba, hbqno, hbq_buf);
}