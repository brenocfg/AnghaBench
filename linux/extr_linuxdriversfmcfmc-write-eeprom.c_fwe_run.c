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
struct fmc_device {int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*) ; 
 int fwe_run_bin (struct fmc_device*,struct firmware const*) ; 
 int fwe_run_tlv (struct fmc_device*,struct firmware const*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int fwe_run(struct fmc_device *fmc, const struct firmware *fw, char *s)
{
	char *last4 = s + strlen(s) - 4;
	int err;

	if (!strcmp(last4, ".bin"))
		return fwe_run_bin(fmc, fw);
	if (!strcmp(last4, ".tlv")) {
		err = fwe_run_tlv(fmc, fw, 0);
		if (!err)
			err = fwe_run_tlv(fmc, fw, 1);
		return err;
	}
	dev_err(&fmc->dev, "invalid file name \"%s\"\n", s);
	return -EINVAL;
}