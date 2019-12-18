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
struct seq_file {struct adapter* private; } ;
struct adapter {int /*<<< orphan*/  pf; int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_PARAMS_MNEM_DEV ; 
 scalar_t__ FW_PARAMS_MNEM_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_DEV_DIAG ; 
 scalar_t__ FW_PARAMS_PARAM_X_V (int /*<<< orphan*/ ) ; 
 scalar_t__ FW_PARAMS_PARAM_Y_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAM_DEV_DIAG_TMP ; 
 int /*<<< orphan*/  FW_PARAM_DEV_DIAG_VDD ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int t4_query_params (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int sensors_show(struct seq_file *seq, void *v)
{
	struct adapter *adap = seq->private;
	u32 param[7], val[7];
	int ret;

	/* Note that if the sensors haven't been initialized and turned on
	 * we'll get values of 0, so treat those as "<unknown>" ...
	 */
	param[0] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		    FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_DIAG) |
		    FW_PARAMS_PARAM_Y_V(FW_PARAM_DEV_DIAG_TMP));
	param[1] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		    FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_DIAG) |
		    FW_PARAMS_PARAM_Y_V(FW_PARAM_DEV_DIAG_VDD));
	ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 2,
			      param, val);

	if (ret < 0 || val[0] == 0)
		seq_puts(seq, "Temperature: <unknown>\n");
	else
		seq_printf(seq, "Temperature: %dC\n", val[0]);

	if (ret < 0 || val[1] == 0)
		seq_puts(seq, "Core VDD:    <unknown>\n");
	else
		seq_printf(seq, "Core VDD:    %dmV\n", val[1]);

	return 0;
}