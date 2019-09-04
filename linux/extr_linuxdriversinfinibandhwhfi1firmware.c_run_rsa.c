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
typedef  int u64 ;
typedef  int u32 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  KEY_SIZE ; 
 int /*<<< orphan*/  MISC_CFG_FW_CTRL ; 
 int MISC_CFG_FW_CTRL_RSA_STATUS_SHIFT ; 
 int MISC_CFG_FW_CTRL_RSA_STATUS_SMASK ; 
 int /*<<< orphan*/  MISC_CFG_RSA_CMD ; 
 int /*<<< orphan*/  MISC_CFG_RSA_SIGNATURE ; 
 int /*<<< orphan*/  MISC_ERR_CLEAR ; 
 int /*<<< orphan*/  MISC_ERR_STATUS ; 
 int MISC_ERR_STATUS_MISC_FW_AUTH_FAILED_ERR_SMASK ; 
 int MISC_ERR_STATUS_MISC_KEY_MISMATCH_ERR_SMASK ; 
 int RSA_CMD_INIT ; 
 int RSA_CMD_START ; 
 int /*<<< orphan*/  RSA_ENGINE_TIMEOUT ; 
 int RSA_STATUS_DONE ; 
 int RSA_STATUS_FAILED ; 
 int RSA_STATUS_IDLE ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,char const*) ; 
 int /*<<< orphan*/  dd_dev_warn (struct hfi1_devdata*,char*,char const*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_rsa_data (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int run_rsa(struct hfi1_devdata *dd, const char *who,
		   const u8 *signature)
{
	unsigned long timeout;
	u64 reg;
	u32 status;
	int ret = 0;

	/* write the signature */
	write_rsa_data(dd, MISC_CFG_RSA_SIGNATURE, signature, KEY_SIZE);

	/* initialize RSA */
	write_csr(dd, MISC_CFG_RSA_CMD, RSA_CMD_INIT);

	/*
	 * Make sure the engine is idle and insert a delay between the two
	 * writes to MISC_CFG_RSA_CMD.
	 */
	status = (read_csr(dd, MISC_CFG_FW_CTRL)
			   & MISC_CFG_FW_CTRL_RSA_STATUS_SMASK)
			     >> MISC_CFG_FW_CTRL_RSA_STATUS_SHIFT;
	if (status != RSA_STATUS_IDLE) {
		dd_dev_err(dd, "%s security engine not idle - giving up\n",
			   who);
		return -EBUSY;
	}

	/* start RSA */
	write_csr(dd, MISC_CFG_RSA_CMD, RSA_CMD_START);

	/*
	 * Look for the result.
	 *
	 * The RSA engine is hooked up to two MISC errors.  The driver
	 * masks these errors as they do not respond to the standard
	 * error "clear down" mechanism.  Look for these errors here and
	 * clear them when possible.  This routine will exit with the
	 * errors of the current run still set.
	 *
	 * MISC_FW_AUTH_FAILED_ERR
	 *	Firmware authorization failed.  This can be cleared by
	 *	re-initializing the RSA engine, then clearing the status bit.
	 *	Do not re-init the RSA angine immediately after a successful
	 *	run - this will reset the current authorization.
	 *
	 * MISC_KEY_MISMATCH_ERR
	 *	Key does not match.  The only way to clear this is to load
	 *	a matching key then clear the status bit.  If this error
	 *	is raised, it will persist outside of this routine until a
	 *	matching key is loaded.
	 */
	timeout = msecs_to_jiffies(RSA_ENGINE_TIMEOUT) + jiffies;
	while (1) {
		status = (read_csr(dd, MISC_CFG_FW_CTRL)
			   & MISC_CFG_FW_CTRL_RSA_STATUS_SMASK)
			     >> MISC_CFG_FW_CTRL_RSA_STATUS_SHIFT;

		if (status == RSA_STATUS_IDLE) {
			/* should not happen */
			dd_dev_err(dd, "%s firmware security bad idle state\n",
				   who);
			ret = -EINVAL;
			break;
		} else if (status == RSA_STATUS_DONE) {
			/* finished successfully */
			break;
		} else if (status == RSA_STATUS_FAILED) {
			/* finished unsuccessfully */
			ret = -EINVAL;
			break;
		}
		/* else still active */

		if (time_after(jiffies, timeout)) {
			/*
			 * Timed out while active.  We can't reset the engine
			 * if it is stuck active, but run through the
			 * error code to see what error bits are set.
			 */
			dd_dev_err(dd, "%s firmware security time out\n", who);
			ret = -ETIMEDOUT;
			break;
		}

		msleep(20);
	}

	/*
	 * Arrive here on success or failure.  Clear all RSA engine
	 * errors.  All current errors will stick - the RSA logic is keeping
	 * error high.  All previous errors will clear - the RSA logic
	 * is not keeping the error high.
	 */
	write_csr(dd, MISC_ERR_CLEAR,
		  MISC_ERR_STATUS_MISC_FW_AUTH_FAILED_ERR_SMASK |
		  MISC_ERR_STATUS_MISC_KEY_MISMATCH_ERR_SMASK);
	/*
	 * All that is left are the current errors.  Print warnings on
	 * authorization failure details, if any.  Firmware authorization
	 * can be retried, so these are only warnings.
	 */
	reg = read_csr(dd, MISC_ERR_STATUS);
	if (ret) {
		if (reg & MISC_ERR_STATUS_MISC_FW_AUTH_FAILED_ERR_SMASK)
			dd_dev_warn(dd, "%s firmware authorization failed\n",
				    who);
		if (reg & MISC_ERR_STATUS_MISC_KEY_MISMATCH_ERR_SMASK)
			dd_dev_warn(dd, "%s firmware key mismatch\n", who);
	}

	return ret;
}