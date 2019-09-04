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
struct tpm_tis_data {int /*<<< orphan*/  int_queue; } ;
struct tpm_chip {unsigned long timeout_a; int flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 long ERESTARTSYS ; 
 int /*<<< orphan*/  TIF_SIGPENDING ; 
 int /*<<< orphan*/  TPM_ACCESS (int) ; 
 int /*<<< orphan*/  TPM_ACCESS_REQUEST_USE ; 
 int TPM_CHIP_FLAG_IRQ ; 
 int /*<<< orphan*/  TPM_TIMEOUT ; 
 scalar_t__ check_locality (struct tpm_chip*,int) ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 struct tpm_tis_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 scalar_t__ freezing (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  tpm_msleep (int /*<<< orphan*/ ) ; 
 long tpm_tis_write8 (struct tpm_tis_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,scalar_t__,unsigned long) ; 

__attribute__((used)) static int request_locality(struct tpm_chip *chip, int l)
{
	struct tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	unsigned long stop, timeout;
	long rc;

	if (check_locality(chip, l))
		return l;

	rc = tpm_tis_write8(priv, TPM_ACCESS(l), TPM_ACCESS_REQUEST_USE);
	if (rc < 0)
		return rc;

	stop = jiffies + chip->timeout_a;

	if (chip->flags & TPM_CHIP_FLAG_IRQ) {
again:
		timeout = stop - jiffies;
		if ((long)timeout <= 0)
			return -1;
		rc = wait_event_interruptible_timeout(priv->int_queue,
						      (check_locality
						       (chip, l)),
						      timeout);
		if (rc > 0)
			return l;
		if (rc == -ERESTARTSYS && freezing(current)) {
			clear_thread_flag(TIF_SIGPENDING);
			goto again;
		}
	} else {
		/* wait for burstcount */
		do {
			if (check_locality(chip, l))
				return l;
			tpm_msleep(TPM_TIMEOUT);
		} while (time_before(jiffies, stop));
	}
	return -1;
}