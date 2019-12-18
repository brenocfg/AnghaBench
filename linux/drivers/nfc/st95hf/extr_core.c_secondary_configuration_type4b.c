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
struct st95hf_context {TYPE_1__* nfcdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ISO14443B_DEMOGAIN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int st95hf_send_recv_cmd (struct st95hf_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int secondary_configuration_type4b(struct st95hf_context *stcontext)
{
	int result = 0;
	struct device *dev = &stcontext->nfcdev->dev;

	result = st95hf_send_recv_cmd(stcontext,
				      CMD_ISO14443B_DEMOGAIN,
				      0,
				      NULL,
				      true);
	if (result)
		dev_err(dev, "type b demogain cmd, err = 0x%x\n", result);

	return result;
}