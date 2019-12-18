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
 int /*<<< orphan*/  M_CAN_ILE ; 
 int /*<<< orphan*/  m_can_write (struct m_can_classdev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void m_can_disable_all_interrupts(struct m_can_classdev *cdev)
{
	m_can_write(cdev, M_CAN_ILE, 0x0);
}