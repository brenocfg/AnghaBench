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
struct tpm_chip {scalar_t__ timeout_adjusted; int /*<<< orphan*/  timeout_d; int /*<<< orphan*/  timeout_c; int /*<<< orphan*/  timeout_b; int /*<<< orphan*/  timeout_a; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int jiffies_to_usecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int,char*) ; 
 struct tpm_chip* to_tpm_chip (struct device*) ; 

__attribute__((used)) static ssize_t timeouts_show(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	struct tpm_chip *chip = to_tpm_chip(dev);

	return sprintf(buf, "%d %d %d %d [%s]\n",
		       jiffies_to_usecs(chip->timeout_a),
		       jiffies_to_usecs(chip->timeout_b),
		       jiffies_to_usecs(chip->timeout_c),
		       jiffies_to_usecs(chip->timeout_d),
		       chip->timeout_adjusted
		       ? "adjusted" : "original");
}