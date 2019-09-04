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
typedef  scalar_t__ u32 ;
struct m_can_priv {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CCCR_CCE ; 
 scalar_t__ CCCR_INIT ; 
 int /*<<< orphan*/  M_CAN_CCCR ; 
 scalar_t__ m_can_read (struct m_can_priv const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_can_write (struct m_can_priv const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void m_can_config_endisable(const struct m_can_priv *priv,
					  bool enable)
{
	u32 cccr = m_can_read(priv, M_CAN_CCCR);
	u32 timeout = 10;
	u32 val = 0;

	if (enable) {
		/* enable m_can configuration */
		m_can_write(priv, M_CAN_CCCR, cccr | CCCR_INIT);
		udelay(5);
		/* CCCR.CCE can only be set/reset while CCCR.INIT = '1' */
		m_can_write(priv, M_CAN_CCCR, cccr | CCCR_INIT | CCCR_CCE);
	} else {
		m_can_write(priv, M_CAN_CCCR, cccr & ~(CCCR_INIT | CCCR_CCE));
	}

	/* there's a delay for module initialization */
	if (enable)
		val = CCCR_INIT | CCCR_CCE;

	while ((m_can_read(priv, M_CAN_CCCR) & (CCCR_INIT | CCCR_CCE)) != val) {
		if (timeout == 0) {
			netdev_warn(priv->dev, "Failed to init module\n");
			return;
		}
		timeout--;
		udelay(1);
	}
}