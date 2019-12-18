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
typedef  int /*<<< orphan*/  u32 ;
struct m_can_classdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCCR_NISO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  M_CAN_CCCR ; 
 int /*<<< orphan*/  m_can_config_endisable (struct m_can_classdev*,int) ; 
 int /*<<< orphan*/  m_can_read (struct m_can_classdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_can_write (struct m_can_classdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static bool m_can_niso_supported(struct m_can_classdev *cdev)
{
	u32 cccr_reg, cccr_poll = 0;
	int niso_timeout = -ETIMEDOUT;
	int i;

	m_can_config_endisable(cdev, true);
	cccr_reg = m_can_read(cdev, M_CAN_CCCR);
	cccr_reg |= CCCR_NISO;
	m_can_write(cdev, M_CAN_CCCR, cccr_reg);

	for (i = 0; i <= 10; i++) {
		cccr_poll = m_can_read(cdev, M_CAN_CCCR);
		if (cccr_poll == cccr_reg) {
			niso_timeout = 0;
			break;
		}

		usleep_range(1, 5);
	}

	/* Clear NISO */
	cccr_reg &= ~(CCCR_NISO);
	m_can_write(cdev, M_CAN_CCCR, cccr_reg);

	m_can_config_endisable(cdev, false);

	/* return false if time out (-ETIMEDOUT), else return true */
	return !niso_timeout;
}