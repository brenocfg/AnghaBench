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
typedef  int /*<<< orphan*/  u8 ;
struct pca953x_chip {int (* read_regs ) (struct pca953x_chip*,int,int /*<<< orphan*/ *) ;TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int stub1 (struct pca953x_chip*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pca953x_read_regs(struct pca953x_chip *chip, int reg, u8 *val)
{
	int ret;

	ret = chip->read_regs(chip, reg, val);
	if (ret < 0) {
		dev_err(&chip->client->dev, "failed reading register\n");
		return ret;
	}

	return 0;
}