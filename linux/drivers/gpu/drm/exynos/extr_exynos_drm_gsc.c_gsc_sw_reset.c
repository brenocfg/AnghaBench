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
typedef  int u32 ;
struct gsc_context {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int EBUSY ; 
 int /*<<< orphan*/  GSC_IN_BASE_ADDR_CB_MASK ; 
 int /*<<< orphan*/  GSC_IN_BASE_ADDR_CR_MASK ; 
 int GSC_IN_BASE_ADDR_MASK ; 
 int GSC_IN_BASE_ADDR_PINGPONG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSC_IN_BASE_ADDR_Y_MASK ; 
 int /*<<< orphan*/  GSC_OUT_BASE_ADDR_CB_MASK ; 
 int /*<<< orphan*/  GSC_OUT_BASE_ADDR_CR_MASK ; 
 int GSC_OUT_BASE_ADDR_MASK ; 
 int GSC_OUT_BASE_ADDR_PINGPONG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSC_OUT_BASE_ADDR_Y_MASK ; 
 int GSC_RESET_TIMEOUT ; 
 int /*<<< orphan*/  GSC_SW_RESET ; 
 int GSC_SW_RESET_SRESET ; 
 int gsc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsc_write (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int gsc_sw_reset(struct gsc_context *ctx)
{
	u32 cfg;
	int count = GSC_RESET_TIMEOUT;

	/* s/w reset */
	cfg = (GSC_SW_RESET_SRESET);
	gsc_write(cfg, GSC_SW_RESET);

	/* wait s/w reset complete */
	while (count--) {
		cfg = gsc_read(GSC_SW_RESET);
		if (!cfg)
			break;
		usleep_range(1000, 2000);
	}

	if (cfg) {
		DRM_DEV_ERROR(ctx->dev, "failed to reset gsc h/w.\n");
		return -EBUSY;
	}

	/* reset sequence */
	cfg = gsc_read(GSC_IN_BASE_ADDR_Y_MASK);
	cfg |= (GSC_IN_BASE_ADDR_MASK |
		GSC_IN_BASE_ADDR_PINGPONG(0));
	gsc_write(cfg, GSC_IN_BASE_ADDR_Y_MASK);
	gsc_write(cfg, GSC_IN_BASE_ADDR_CB_MASK);
	gsc_write(cfg, GSC_IN_BASE_ADDR_CR_MASK);

	cfg = gsc_read(GSC_OUT_BASE_ADDR_Y_MASK);
	cfg |= (GSC_OUT_BASE_ADDR_MASK |
		GSC_OUT_BASE_ADDR_PINGPONG(0));
	gsc_write(cfg, GSC_OUT_BASE_ADDR_Y_MASK);
	gsc_write(cfg, GSC_OUT_BASE_ADDR_CB_MASK);
	gsc_write(cfg, GSC_OUT_BASE_ADDR_CR_MASK);

	return 0;
}