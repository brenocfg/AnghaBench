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
struct m_can_classdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CAN_TXFQS ; 
 int TXFQS_TFQF ; 
 int m_can_read (struct m_can_classdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool m_can_tx_fifo_full(struct m_can_classdev *cdev)
{
		return !!(m_can_read(cdev, M_CAN_TXFQS) & TXFQS_TFQF);
}