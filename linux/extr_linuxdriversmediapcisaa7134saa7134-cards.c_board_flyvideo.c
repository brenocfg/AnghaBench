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
struct saa7134_dev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void board_flyvideo(struct saa7134_dev *dev)
{
	pr_warn("%s: there are different flyvideo cards with different tuners\n"
		"%s: out there, you might have to use the tuner=<nr> insmod\n"
		"%s: option to override the default value.\n",
		dev->name, dev->name, dev->name);
}