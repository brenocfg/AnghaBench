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
struct softing {TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int _softing_fct_cmd (struct softing*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ *,char*,char const*,int) ; 

__attribute__((used)) static int softing_fct_cmd(struct softing *card, int16_t cmd, const char *msg)
{
	int ret;

	ret = _softing_fct_cmd(card, cmd, 0, msg);
	if (ret > 0) {
		dev_alert(&card->pdev->dev, "%s returned %u\n", msg, ret);
		ret = -EIO;
	}
	return ret;
}