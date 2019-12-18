#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct dcon_priv {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* bus_stabilize_wiggle ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCON_REG_ID ; 
 int /*<<< orphan*/  EC_DCON_POWER_MODE ; 
 int dcon_hw_init (struct dcon_priv*,int /*<<< orphan*/ ) ; 
 int dcon_read (struct dcon_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  olpc_board (int) ; 
 int /*<<< orphan*/  olpc_board_at_least (int /*<<< orphan*/ ) ; 
 int olpc_ec_cmd (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* pdata ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int dcon_bus_stabilize(struct dcon_priv *dcon, int is_powered_down)
{
	unsigned long timeout;
	u8 pm;
	int x;

power_up:
	if (is_powered_down) {
		pm = 1;
		x = olpc_ec_cmd(EC_DCON_POWER_MODE, &pm, 1, NULL, 0);
		if (x) {
			pr_warn("unable to force dcon to power up: %d!\n", x);
			return x;
		}
		usleep_range(10000, 11000);  /* we'll be conservative */
	}

	pdata->bus_stabilize_wiggle();

	for (x = -1, timeout = 50; timeout && x < 0; timeout--) {
		usleep_range(1000, 1100);
		x = dcon_read(dcon, DCON_REG_ID);
	}
	if (x < 0) {
		pr_err("unable to stabilize dcon's smbus, reasserting power and praying.\n");
		BUG_ON(olpc_board_at_least(olpc_board(0xc2)));
		pm = 0;
		olpc_ec_cmd(EC_DCON_POWER_MODE, &pm, 1, NULL, 0);
		msleep(100);
		is_powered_down = 1;
		goto power_up;	/* argh, stupid hardware.. */
	}

	if (is_powered_down)
		return dcon_hw_init(dcon, 0);
	return 0;
}