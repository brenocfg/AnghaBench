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
struct tpm_nsc_priv {scalar_t__ base; } ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ NSC_COMMAND ; 
 int /*<<< orphan*/  NSC_COMMAND_CANCEL ; 
 int /*<<< orphan*/  NSC_COMMAND_EOC ; 
 int /*<<< orphan*/  NSC_COMMAND_NORMAL ; 
 scalar_t__ NSC_DATA ; 
 int /*<<< orphan*/  NSC_STATUS_IBF ; 
 int /*<<< orphan*/  NSC_STATUS_IBR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct tpm_nsc_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 scalar_t__ nsc_wait_for_ready (struct tpm_chip*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ wait_for_stat (struct tpm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tpm_nsc_send(struct tpm_chip *chip, u8 * buf, size_t count)
{
	struct tpm_nsc_priv *priv = dev_get_drvdata(&chip->dev);
	u8 data;
	int i;

	/*
	 * If we hit the chip with back to back commands it locks up
	 * and never set IBF. Hitting it with this "hammer" seems to
	 * fix it. Not sure why this is needed, we followed the flow
	 * chart in the manual to the letter.
	 */
	outb(NSC_COMMAND_CANCEL, priv->base + NSC_COMMAND);

	if (nsc_wait_for_ready(chip) != 0)
		return -EIO;

	if (wait_for_stat(chip, NSC_STATUS_IBF, 0, &data) < 0) {
		dev_err(&chip->dev, "IBF timeout\n");
		return -EIO;
	}

	outb(NSC_COMMAND_NORMAL, priv->base + NSC_COMMAND);
	if (wait_for_stat(chip, NSC_STATUS_IBR, NSC_STATUS_IBR, &data) < 0) {
		dev_err(&chip->dev, "IBR timeout\n");
		return -EIO;
	}

	for (i = 0; i < count; i++) {
		if (wait_for_stat(chip, NSC_STATUS_IBF, 0, &data) < 0) {
			dev_err(&chip->dev,
				"IBF timeout (while writing data)\n");
			return -EIO;
		}
		outb(buf[i], priv->base + NSC_DATA);
	}

	if (wait_for_stat(chip, NSC_STATUS_IBF, 0, &data) < 0) {
		dev_err(&chip->dev, "IBF timeout\n");
		return -EIO;
	}
	outb(NSC_COMMAND_EOC, priv->base + NSC_COMMAND);

	return 0;
}