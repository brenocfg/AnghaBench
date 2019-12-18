#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  bah; int /*<<< orphan*/  bal; int /*<<< orphan*/  len; int /*<<< orphan*/  head; int /*<<< orphan*/  tail; } ;
struct TYPE_4__ {int /*<<< orphan*/  bah; int /*<<< orphan*/  bal; int /*<<< orphan*/  len; int /*<<< orphan*/  head; int /*<<< orphan*/  tail; } ;
struct TYPE_6__ {TYPE_2__ arq; TYPE_1__ asq; } ;
struct iavf_hw {TYPE_3__ aq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IAVF_VF_ARQBAH1 ; 
 int /*<<< orphan*/  IAVF_VF_ARQBAL1 ; 
 int /*<<< orphan*/  IAVF_VF_ARQH1 ; 
 int /*<<< orphan*/  IAVF_VF_ARQLEN1 ; 
 int /*<<< orphan*/  IAVF_VF_ARQT1 ; 
 int /*<<< orphan*/  IAVF_VF_ATQBAH1 ; 
 int /*<<< orphan*/  IAVF_VF_ATQBAL1 ; 
 int /*<<< orphan*/  IAVF_VF_ATQH1 ; 
 int /*<<< orphan*/  IAVF_VF_ATQLEN1 ; 
 int /*<<< orphan*/  IAVF_VF_ATQT1 ; 

__attribute__((used)) static void iavf_adminq_init_regs(struct iavf_hw *hw)
{
	/* set head and tail registers in our local struct */
	hw->aq.asq.tail = IAVF_VF_ATQT1;
	hw->aq.asq.head = IAVF_VF_ATQH1;
	hw->aq.asq.len  = IAVF_VF_ATQLEN1;
	hw->aq.asq.bal  = IAVF_VF_ATQBAL1;
	hw->aq.asq.bah  = IAVF_VF_ATQBAH1;
	hw->aq.arq.tail = IAVF_VF_ARQT1;
	hw->aq.arq.head = IAVF_VF_ARQH1;
	hw->aq.arq.len  = IAVF_VF_ARQLEN1;
	hw->aq.arq.bal  = IAVF_VF_ARQBAL1;
	hw->aq.arq.bah  = IAVF_VF_ARQBAH1;
}