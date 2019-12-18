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
struct ethsw_core {int learning; int /*<<< orphan*/  dev; int /*<<< orphan*/  dpsw_handle; int /*<<< orphan*/  mc_io; } ;
typedef  enum dpsw_fdb_learning_mode { ____Placeholder_dpsw_fdb_learning_mode } dpsw_fdb_learning_mode ;

/* Variables and functions */
 int DPSW_FDB_LEARNING_MODE_DIS ; 
 int DPSW_FDB_LEARNING_MODE_HW ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int dpsw_fdb_set_learning_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ethsw_set_learning(struct ethsw_core *ethsw, bool enable)
{
	enum dpsw_fdb_learning_mode learn_mode;
	int err;

	if (enable)
		learn_mode = DPSW_FDB_LEARNING_MODE_HW;
	else
		learn_mode = DPSW_FDB_LEARNING_MODE_DIS;

	err = dpsw_fdb_set_learning_mode(ethsw->mc_io, 0, ethsw->dpsw_handle, 0,
					 learn_mode);
	if (err) {
		dev_err(ethsw->dev, "dpsw_fdb_set_learning_mode err %d\n", err);
		return err;
	}
	ethsw->learning = enable;

	return 0;
}