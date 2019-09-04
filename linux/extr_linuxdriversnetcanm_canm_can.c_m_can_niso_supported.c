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
struct m_can_priv {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCCR_NISO ; 
 scalar_t__ M_CAN_CCCR ; 
 int /*<<< orphan*/  m_can_config_endisable (struct m_can_priv const*,int) ; 
 int /*<<< orphan*/  m_can_read (struct m_can_priv const*,scalar_t__) ; 
 int /*<<< orphan*/  m_can_write (struct m_can_priv const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int readl_poll_timeout (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool m_can_niso_supported(const struct m_can_priv *priv)
{
	u32 cccr_reg, cccr_poll;
	int niso_timeout;

	m_can_config_endisable(priv, true);
	cccr_reg = m_can_read(priv, M_CAN_CCCR);
	cccr_reg |= CCCR_NISO;
	m_can_write(priv, M_CAN_CCCR, cccr_reg);

	niso_timeout = readl_poll_timeout((priv->base + M_CAN_CCCR), cccr_poll,
					  (cccr_poll == cccr_reg), 0, 10);

	/* Clear NISO */
	cccr_reg &= ~(CCCR_NISO);
	m_can_write(priv, M_CAN_CCCR, cccr_reg);

	m_can_config_endisable(priv, false);

	/* return false if time out (-ETIMEDOUT), else return true */
	return !niso_timeout;
}