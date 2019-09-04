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
typedef  int u32 ;
typedef  int u16 ;
struct mdfld_dsi_pkg_sender {int mipi_intr_stat_reg; int mipi_hs_gen_data_reg; int mipi_lp_gen_data_reg; int /*<<< orphan*/  lock; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int MDFLD_DSI_READ_MAX_COUNT ; 
 int REG_READ (int) ; 
 int /*<<< orphan*/  REG_WRITE (int,int) ; 
 int /*<<< orphan*/  send_pkg (struct mdfld_dsi_pkg_sender*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int __read_panel_data(struct mdfld_dsi_pkg_sender *sender, u8 data_type,
			u8 *data, u16 len, u32 *data_out, u16 len_out, bool hs)
{
	unsigned long flags;
	struct drm_device *dev;
	int i;
	u32 gen_data_reg;
	int retry = MDFLD_DSI_READ_MAX_COUNT;

	if (!sender || !data_out || !len_out) {
		DRM_ERROR("Invalid parameters\n");
		return -EINVAL;
	}

	dev = sender->dev;

	/**
	 * do reading.
	 * 0) send out generic read request
	 * 1) polling read data avail interrupt
	 * 2) read data
	 */
	spin_lock_irqsave(&sender->lock, flags);

	REG_WRITE(sender->mipi_intr_stat_reg, BIT(29));

	if ((REG_READ(sender->mipi_intr_stat_reg) & BIT(29)))
		DRM_ERROR("Can NOT clean read data valid interrupt\n");

	/*send out read request*/
	send_pkg(sender, data_type, data, len, hs);

	/*polling read data avail interrupt*/
	while (retry && !(REG_READ(sender->mipi_intr_stat_reg) & BIT(29))) {
		udelay(100);
		retry--;
	}

	if (!retry) {
		spin_unlock_irqrestore(&sender->lock, flags);
		return -ETIMEDOUT;
	}

	REG_WRITE(sender->mipi_intr_stat_reg, BIT(29));

	/*read data*/
	if (hs)
		gen_data_reg = sender->mipi_hs_gen_data_reg;
	else
		gen_data_reg = sender->mipi_lp_gen_data_reg;

	for (i = 0; i < len_out; i++)
		*(data_out + i) = REG_READ(gen_data_reg);

	spin_unlock_irqrestore(&sender->lock, flags);

	return 0;
}